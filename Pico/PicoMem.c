/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*            Chunk store            */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/* memory architecture                                                    */
/*                                                                        */
/* memory is a partition of chunks; a chunk consists of a sequence of     */
/* consecutive cells; each first cell contains either the size of the     */
/* chunk or -only during garbage collection- a link; each following cell  */
/* either contains a number, a link, a pointer to a chunk or raw data     */
/*                                                                        */
/* the header cell at the beginning of a chunk is composed as follows:    */
/*                                                                        */
/* chunk-size      -> [<--------size------->|<-tag->|r|1|f|1]             */
/*                                                                        */
/*      size -> 24-bit chunk size, not counting first cel (unsigned)      */
/*       tag -> 4-bit user flag                                           */
/*         r -> 1-bit raw data indicator                                  */
/*         f -> 1-bit freebit (only used during garbage collection)       */
/*                                                                        */
/* a cell containing an embedded number has the following structure:      */
/*                                                                        */
/* embedded number -> [<--------------number------------->|0]             */
/*                                                                        */
/*    number -> 31-bit integer (signed)                                   */
/*                                                                        */
/* a cell containing a pointer into chunk memory is composed as follows:  */
/*                                                                        */
/* chunk-pointer   -> [<-------------offset---------->|0|f|1]             */
/*                                                                        */
/*    offset -> 29-bit offset into chunk store (unsigned)                 */
/*         f -> 1-bit freebit (only used during garbage collection)       */
/*                                                                        */
/* a cell containing raw data is composed as follows:                     */
/*                                                                        */
/* chunk-pointer   -> [<--------------value---------------->]             */
/*                                                                        */
/*    value -> 32-bit anonymous number (unsigned)                         */
/*                                                                        */
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*                     sweep DFA for chunk store                          */        
/*------------------------------------------------------------------------*/
/*        P -> |       |                             |       |            */    
/*             '-------'                             '-------'            */    
/*                                     \                 ^                */    
/*                                  ====\                |                */    
/*                                  ====/                '---------.      */    
/*                                     /                           |      */    
/*                                                                 |      */    
/*        ___ ___ _____ ___ ___                 ___ ___ _____ ___ _|_     */    
/*       |f  |f  |f    |f  |f  |               |b  |f  |f    |f  |f| |    */    
/*  C -> | # | o | ... | o | o |               | # | o | ... | o | o |    */    
/*       '---'-|-'-----'-|-'-|-'               '---'-|-'-----'-|-'---'    */    
/*             :         :   |                       :         :   ^      */    
/*                           |                                     |      */    
/*                           |                                     P      */    
/*                           v                                            */    
/*                        _______                               _______   */    
/*                       |       |                        C -> |       |  */    
/*------------------------------------------------------------------------*/
/*              |       |                             |       |           */    
/*              '-------'                             '-------'           */    
/*                  ^                  \                  ^               */    
/*                  |               ====\                 |               */    
/*                  '-.             ====/               .-'               */    
/*                    |                /                |                 */    
/*                    |                                 |                 */    
/*        ______ ___ _|_ ______                 ______ _|_ ___ ______     */    
/*       |b     |f  |f| |   f  |               |b     |f| |f  |   f  |    */    
/*       | # .. | o | o | .. o |               | # .. | o | o | .. o |    */    
/*       '------'/--'---'----|-'               '------'---'--\'----|-'    */    
/*              /     ^      :                          ^   ^ \    :      */    
/*             /      |                                 |   |  \          */    
/*            /       P     ____                        P   |   \  ____   */    
/*           /         ____|                                |    -|       */    
/*          /         |    '----                            |     '----   */    
/*     ____/__       _|_ ______              _______       _|_ ______     */
/*    |       | C ->|b| |      |        C ->|       |     |b| |      |    */
/*    |             | o |  ..               |             | o |  ..       */    
/*------------------------------------------------------------------------*/
/*              |       |                        P -> |       |           */    
/*              '-------'                             '-------'           */    
/*                  ^                  \                                  */    
/*                  |               ====\                                 */    
/*             .----'               ====/                                 */    
/*             |                       /                                  */    
/*             |                                                          */    
/*        ___ _|_ _________ ___                 ___ ___ _________ ___     */    
/*       |b  |f| |f        |f  |               |b  |f  |f        |f  |    */    
/*       | # | o |   ...   | o |           C ->| # | o |   ...   | o |    */    
/*       '---'---'---------'-|-'               '---'--\'---------'-|-'    */    
/*             ^             :                       ^ \           :      */    
/*             |                                     |  \                 */    
/*             P     ____                            |   \  ____          */    
/*              ____|                                |    -|              */    
/*             |    '----                            |     '----          */    
/*            _|_ ______                            _|_ ______            */    
/*       C ->|b| |      |                          |b| |      |           */ 
/*           | o |  ..                             | o |  ..              */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"

/* private constants */

const static _EXP_TYPE_ rhbp = {0,0,0,0,0,0};
const static _EXP_TYPE_ rhbP = {0,0,0,0,0,1};
const static _EXP_TYPE_ RhbP = {0,0,1,0,0,1};
const static _EXP_TYPE_ rHbP = {0,0,0,1,0,1};
const static _EXP_TYPE_ RHbP = {0,0,1,1,0,1};
const static _EXP_TYPE_ rhBP = {0,0,0,0,1,1};
const static _EXP_TYPE_ rHBP = {0,0,0,1,1,1};
const static _EXP_TYPE_ RhBP = {0,0,1,0,1,1};
const static _EXP_TYPE_ RHBP = {0,0,1,1,1,1};

/* private variables */

static _UNS_TYPE_ sweep_prv;
static _UNS_TYPE_ sweep_cur;
static _EXP_TYPE_ sweep_cel;
static _UNS_TYPE_ sweep_ofs;
static _EXI_TYPE_ sweep_exi;
static _CNT_TYPE_ sweep_tab[16];

/* public variables */

_EXP_TYPE_ *_mem_STORE_ = 0;
_UNS_TYPE_  _mem_FREE_ = 0;
_UNS_TYPE_  _mem_TOP_ = 0;

/* private functions */

static _NIL_TYPE_ XhbP_fun(_NIL_TYPE_)
 { _mem_STORE_[sweep_cur].ptr.ofs = sweep_prv;
   sweep_prv = sweep_cur;
   sweep_cur = sweep_cel.ptr.ofs;
   return; }

static _NIL_TYPE_ rHbP_fun(_NIL_TYPE_)
 { _mem_STORE_[sweep_cur].hdr.bsy = 1;
   sweep_cur += sweep_cel.hdr.siz;
   return; }

static _NIL_TYPE_ RHbP_fun(_NIL_TYPE_)
 { _mem_STORE_[sweep_cur].hdr.bsy = 1;
   return; }

static _NIL_TYPE_ XXBP_fun(_NIL_TYPE_)
 { if (sweep_prv >= _mem_TOP_)
     longjmp(sweep_exi, 1);
   sweep_ofs = _mem_STORE_[sweep_prv].ptr.ofs;
   _mem_STORE_[sweep_prv] = sweep_cel;
   _mem_STORE_[sweep_cur] = rhBP;
   _mem_STORE_[sweep_cur].ptr.ofs = sweep_prv;
   sweep_cur = sweep_prv-1;
   sweep_prv = sweep_ofs;
   return; }

static _NIL_TYPE_ XXXX_fun(_NIL_TYPE_)
 { sweep_cur--;
   return; }

static _NIL_TYPE_ sweep(_NIL_TYPE_)
 { sweep_prv = _mem_TOP_;
   sweep_cur = 0;
   if (setjmp(sweep_exi) == 0)
		 { loop:
		     sweep_cel = _mem_STORE_[sweep_cur];   
		     sweep_tab[sweep_cel.swi.sta]();
		     goto loop; }}
   
static _NIL_TYPE_ init_sweep(_NIL_TYPE_)
 { _BYT_TYPE_ idx;
   for(idx = 0; idx < 16; idx++)
     sweep_tab[idx] = XXXX_fun;
   sweep_tab[rhbP.swi.sta] = XhbP_fun;
   sweep_tab[RhbP.swi.sta] = XhbP_fun;
   sweep_tab[rHbP.swi.sta] = rHbP_fun;
   sweep_tab[RHbP.swi.sta] = RHbP_fun;
   sweep_tab[rhBP.swi.sta] = XXBP_fun;
   sweep_tab[rHBP.swi.sta] = XXBP_fun;
   sweep_tab[RhBP.swi.sta] = XXBP_fun;
   sweep_tab[RHBP.swi.sta] = XXBP_fun; }

static _NIL_TYPE_ update(_NIL_TYPE_)
 { _EXP_TYPE_ ptr = rhbP;
   _EXP_TYPE_ cel;          
   _UNS_TYPE_ dst = 0;
   _UNS_TYPE_ src = 0;
   _UNS_TYPE_ ofs, siz;
   while (src < _mem_FREE_)
     { cel = _mem_STORE_[src];
       if (!cel.ptr.hdr)
         { ptr.ptr.ofs = dst;
           do
             { ofs = cel.ptr.ofs;
               cel = _mem_STORE_[ofs];
               _mem_STORE_[ofs] = ptr; }
           while (!cel.ptr.hdr);
           _mem_STORE_[src] = cel; }
       siz = cel.hdr.siz;
       if (cel.hdr.bsy)
         dst += siz + 1;
       src += siz + 1; }}
       
static _NIL_TYPE_ crunch(_NIL_TYPE_)
 { _EXP_TYPE_ cel;
   _UNS_TYPE_ dst = 0;
   _UNS_TYPE_ src = 0;
   _UNS_TYPE_ siz;
   while (src < _mem_FREE_)
     { cel = _mem_STORE_[src];
       siz = cel.hdr.siz;
       if (cel.hdr.bsy)
         { _mem_STORE_[src].hdr.bsy = 0;
           do
             { _mem_STORE_[dst++] = _mem_STORE_[src++]; }
           while (siz--); }
       else
         src += siz + 1; }
   _mem_FREE_ = dst; }

static _UNS_TYPE_ allocate(const _UNS_TYPE_ siz)
 { _UNS_TYPE_ ofs = _mem_FREE_;
   _mem_FREE_ += siz + 1;
   #ifndef NDEBUG
   if (_mem_FREE_ > _mem_TOP_)
     _error_(_MEM_ERROR_);
   #endif
   return ofs; }
   
/* public functions */

_NIL_TYPE_ _mem_setup_(const _ADR_TYPE_ adr,
                       const _UNS_TYPE_ top)
 { _mem_STORE_ = (_EXP_TYPE_ *)adr;
   _mem_TOP_ = top;
   _mem_FREE_ = 0; 
   init_sweep(); }
   
_EXP_TYPE_ _mem_make_nbr_(const _SGN_TYPE_ nbr)
 { _EXP_TYPE_ exp = rhbp;
   exp.nbr.nbr = nbr;
   return exp; }

_EXP_TYPE_ _mem_make_nbu_(const _UNS_TYPE_ nbr)
 { _EXP_TYPE_ exp = rhbp;
   exp.nbu.nbr = nbr;
   return exp; }

_EXP_TYPE_ _mem_make_chunk_(const _UNS_TYPE_ siz,
                            const _TAG_TYPE_ tag)
 { _UNS_TYPE_ ofs = allocate(siz);
   _EXP_TYPE_ hdr = rHbP;
   _EXP_TYPE_ exp = rhbP;
   _UNS_TYPE_ idx = siz;
   hdr.hdr.tag = CHK_TGR(tag);
   hdr.hdr.siz = siz;
   _mem_STORE_[ofs] = hdr;
   exp.ptr.ofs = ofs;
   while (idx--)
     _mem_STORE_[++ofs] = rhbp;
   return exp; }
   
_EXP_TYPE_ _mem_make_raw_(const _UNS_TYPE_ siz,
                          const _TAG_TYPE_ tag)
 { _UNS_TYPE_ ofs = allocate(siz);
   _EXP_TYPE_ hdr = RHbP;
   _EXP_TYPE_ exp = rhbP;
   hdr.hdr.tag = CHK_TGR(tag);
   hdr.hdr.siz = siz;
   _mem_STORE_[ofs] = hdr;
   exp.ptr.ofs = ofs;
   return exp; }

_EXP_TYPE_ _mem_fill_raw_(const _UNS_TYPE_ len,
                          const _TAG_TYPE_ tag,
                          const _ADR_TYPE_ raw)
 { _UNS_TYPE_ siz = (len + _EXP_SIZE_ - 1)/_EXP_SIZE_;
   _UNS_TYPE_ ofs = allocate(siz);
   _EXP_TYPE_ hdr = RHbP;
   _EXP_TYPE_ exp = rhbP;
   hdr.hdr.tag = CHK_TGR(tag);
   hdr.hdr.siz = siz;
   _mem_STORE_[ofs] = hdr;
   exp.ptr.ofs = ofs;
   memcpy(&_mem_STORE_[ofs+1], raw, len);
   return exp; }

_EXP_TYPE_ _mem_make_cont_(const _CNT_TYPE_ cnt)
 { _EXP_TYPE_ exp;
   exp.cnt = cnt;
   return exp; }

_NIL_TYPE_ _mem_reclaim_(const _UNS_TYPE_ mrg)
 { sweep();
   update();
   crunch(); 
   if ((_mem_FREE_ + mrg) > _mem_TOP_)
     _error_(_MEM_ERROR_); }
   
/* debug functions */

#ifndef NDEBUG

#define TAG_MAX 15

_EXP_TYPE_ CHK_NBR(const _EXP_TYPE_ exp)
 { if (exp.nbr.ptr)
     _error_(_EXP_ERROR_);
   return exp; }

_EXP_TYPE_ CHK_PTR(const _EXP_TYPE_ exp)
 { if (!exp.ptr.ptr || (exp.ptr.ofs > _mem_TOP_))
     _error_(_EXP_ERROR_); 
   return exp; }

_EXP_TYPE_ CHK_NRW(const _EXP_TYPE_ exp)
 { if (_mem_STORE_[exp.ptr.ofs].hdr.raw)
     _error_(_EXP_ERROR_);
   return exp; }

_TAG_TYPE_ CHK_TGR(const _TAG_TYPE_ tag)
 { if (tag > TAG_MAX)\
     _error_(_TAG_ERROR_);
   return tag; }

_EXP_TYPE_ CHK_TAG(const _EXP_TYPE_ exp,
                   const _TAG_TYPE_ tag)
 { if (_mem_STORE_[exp.ptr.ofs].hdr.tag != tag)\
     _error_(_TAG_ERROR_);
   return exp; }

_UNS_TYPE_ CHK_RNG(const _UNS_TYPE_ ofs,
                   const _UNS_TYPE_ idx)
 { if ((idx <= 0) || 
       (idx > _mem_STORE_[ofs].hdr.siz))
     _error_(_IDX_ERROR_);
   return ofs+idx; }

#endif
