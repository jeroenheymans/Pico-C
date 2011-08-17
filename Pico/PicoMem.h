/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*            Chunk store            */
/*-----------------------------------*/

/* private macros */

#ifdef NDEBUG

#define CHK_NBR(EXP) (EXP)
#define CHK_PTR(EXP) (EXP) 
#define CHK_NRW(PTR) (PTR)  
#define CHK_TGR(TAG) (TAG)  
#define CHK_TAG(PTR,TAG) (PTR)  
#define CHK_RNG(OFS,IDX) (OFS + IDX)

#else

_EXP_TYPE_ CHK_NBR(const _EXP_TYPE_);
_EXP_TYPE_ CHK_PTR(const _EXP_TYPE_);
_EXP_TYPE_ CHK_NRW(const _EXP_TYPE_);
_TAG_TYPE_ CHK_TGR(const _TAG_TYPE_);
_EXP_TYPE_ CHK_TAG(const _EXP_TYPE_,
                   const _TAG_TYPE_);
_UNS_TYPE_ CHK_RNG(const _UNS_TYPE_,
                   const _UNS_TYPE_);
  
#endif

/* public macros */

#define _mem_claim_SIZ_(SIZ)\
  if (_mem_FREE_ + SIZ + _MEM_CLAIM_ >= _mem_TOP_)\
    _reclaim_(SIZ + _MEM_CLAIM_ + 1)
     
#define _mem_claim_STR_(STR)\
  _mem_claim_SIZ_((strlen(STR) + _EXP_SIZE_)/_EXP_SIZE_)
     
#define _mem_claim_()\
  if (_mem_FREE_ + _MEM_CLAIM_ > _mem_TOP_)\
    _reclaim_(_MEM_CLAIM_)
     
#define _mem_succ_number_(NBR)\
  _mem_make_nbr_(CHK_NBR(NBR).nbr.nbr + 1)
   
#define _mem_chunk_size_(EXP)\
  (_mem_STORE_[CHK_PTR(EXP).ptr.ofs].hdr.siz)

#define _mem_get_tag_(EXP)\
  ((_TAG_TYPE_)_mem_STORE_[CHK_PTR(EXP).ptr.ofs].hdr.tag)
  
#define _mem_is_same_(EXP_1, EXP_2)\
  ((EXP_1).raw == (EXP_2).raw)

#define  _mem_get_nbr_(EXP)\
  (CHK_NBR(EXP).nbr.nbr)
   
#define  _mem_get_nbu_(EXP)\
  (CHK_NBR(EXP).nbu.nbr)
   
#define _mem_is_number_(EXP)\
  (!(EXP).nbr.ptr)

#define _mem_get_exp_(EXP, IDX)\
  _mem_STORE_[CHK_RNG(CHK_NRW(CHK_PTR(EXP)).ptr.ofs,IDX)]
 
#define _mem_get_cnt_(EXP, IDX)\
  _mem_get_exp_(EXP, IDX).cnt
 
#define _mem_set_exp_(EXP, IDX, VAL)\
  _mem_get_exp_(EXP, IDX) = VAL

#define _mem_set_cnt_(EXP, IDX, CNT)\
  _mem_get_cnt_(EXP, IDX) = CNT

#define _mem_cast_raw_(EXP,TAG)\
  &_mem_STORE_[CHK_TAG(CHK_PTR(EXP),TAG).ptr.ofs + 1]

#define _mem_is_raw_(EXP)\
  (_mem_STORE_[CHK_PTR(EXP).ptr.ofs].hdr.raw)

/* public variables */

extern _EXP_TYPE_ *_mem_STORE_;
extern _UNS_TYPE_  _mem_FREE_;
extern _UNS_TYPE_  _mem_TOP_;

/* public prototypes */

_NIL_TYPE_                   _mem_setup_(const _ADR_TYPE_,
                                         const _UNS_TYPE_);
 
_EXP_TYPE_                _mem_make_nbr_(const _SGN_TYPE_);
                                         
_EXP_TYPE_                _mem_make_nbu_(const _UNS_TYPE_);
                                         
_EXP_TYPE_              _mem_make_chunk_(const _UNS_TYPE_,
                                         const _TAG_TYPE_);
                                         
_EXP_TYPE_                _mem_make_raw_(const _UNS_TYPE_,
                                         const _TAG_TYPE_);
                                         
_EXP_TYPE_                _mem_fill_raw_(const _UNS_TYPE_,
                                         const _TAG_TYPE_,
                                         const _ADR_TYPE_);
                                         
_EXP_TYPE_               _mem_make_cont_(const _CNT_TYPE_);

_NIL_TYPE_              _mem_mark_sweep_(      _NIL_TYPE_);

_NIL_TYPE_                 _mem_reclaim_(const _UNS_TYPE_);
