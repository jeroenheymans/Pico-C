/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*           Main program            */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/*                   ABSTRACT GRAMMAR (conceptual view)                   */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* INT       -> [Int]                                                     */
/* FRC       -> [Frc]                                                     */
/* TXT       -> [Txt]                                                     */
/* FUN       -> [Idf] [Exp] [Exp] [Dct]                                   */
/* NAT       -> [Idf] [Nbr]                                               */
/* CNT       -> [Idf] [Exp] [Exp] [Dct] [Stk]                             */
/* TAB       -> [Int] [Exp]*                                              */
/* VAR       -> [Idf]                                                     */
/* APL       -> [Idf] [Exp]                                               */
/* TBL       -> [Idf] [Exp]                                               */
/* DEF       -> [Exp] [Exp]                                               */
/* SET       -> [Exp] [Exp]                                               */
/* DCT       -> [Idf] [Exp] [Dct]                                         */
/* ENV       -> [Dct] [Nbr] [Nbr] [Tab]                                   */
/* VOI       ->                                                           */
/*                                                                        */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                   ABSTRACT GRAMMAR (physical view)                     */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* <void>            -> [_VOI_TAG_]                                       */
/* <number>          -> [_NBR_TAG_,#nbr#]                                 */
/* <fraction>        -> [_FRC_TAG_,#frc#]                                 */
/* <text>            -> [_TXT_TAG_,#txt#]                                 */
/* <function>        -> [_FUN_TAG_,IdfSet,ArgSet,ExpSet,DctSet]           */
/* <native function> -> [_NAT_TAG_,IdfSet,NbrSet]                         */
/* <continuation>    -> [_CNT_TAG_,IdfSet,ArgSet,ExpSet,DctSet,StkSet]    */
/* <table>           -> [_TAB_TAG_,ExpSet,ExpSet, ...  ,ExpSet]           */
/* <variable>        -> [_VAR_TAG_,IdfSet]                                */
/* <application>     -> [_APL_TAG_,IdfSet,ArgSet]                         */
/* <tabulation>      -> [_TBL_TAG_,IdfSet,ExpSet]                         */
/* <definition>      -> [_DEF_TAG_,InvSet,ExpSet]                         */
/* <assignment>      -> [_SET_TAG_,InvSet,ExpSet]                         */
/* <dictionary>      -> [_DCT_TAG_,IdfSet,ExpSet,DctSet]                  */
/* <environment>     -> [_ENV_TAG_,DctSet,NbrSet,NbrSet,TabSet]           */
/*                                                                        */
/*  DctSet       = {<dictionary>,<void>}                                  */
/*  StkSet       = {<stack>}                                              */
/*  IdfSet       = {<text>}                                               */
/*  NbrSet       = {<number>}                                             */
/*  TabSet       = {<table>}                                              */
/*  ArgSet       = TabSet+ExpSet                                          */
/*  InvSet       = {<variable>,                                           */
/*                  <application>,                                        */
/*                  <tabulation>}                                         */
/*  ExpSet       = {<void>,                                               */
/*                  <number>,                                             */
/*                  <fraction>,                                           */
/*                  <text>,                                               */
/*                  <definition>,                                         */
/*                  <assignment>}+InvSet                                  */
/*------------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoRea.h"
#include "PicoEnv.h"
#include "PicoNat.h"
#include "PicoEva.h"
#include "PicoPri.h"

/* private constants */

#define ROOT_SIZE        3
#define GLOBAL_ROOT      1
#define NAMES_ROOT       2
#define ENVIRONMENT_ROOT 3

/* private variables */

static enum 
     { NO_INIT, 
       DISABLED,
       ENABLED }  STATUS = NO_INIT;
static _BYT_TYPE_ SES_IDX;
static _DSC_TYPE_ SES_TAB[_MAX_SES_];
static _EXP_TYPE_ ROOT;
static _EXP_TYPE_ GLOBAL;
static _EXP_TYPE_ ENVIRONMENT;

/* public variables */

_BYT_TYPE_ _DELAY_ = 0;
_BUF_TYPE_ _TEXT_BUF_;
_UNS_TYPE_ _STK_MAX_;
_EXP_TYPE_ _NAMES_;

/* private macros */

#define CTX_INITIALISE(IDX, DCT)\
  _ag_set_TAB_EXP_(ENVIRONMENT, IDX + 1, _env_initialise_(DCT))

#define CTX_CAPTURE(IDX)\
  _env_capture_(_ag_get_TAB_EXP_(ENVIRONMENT, IDX + 1))
  
#define CTX_RESTORE(IDX)\
  _env_restore_(_ag_get_TAB_EXP_(ENVIRONMENT, IDX + 1))
  
#define CTX_VOID(IDX)\
  _ag_set_TAB_EXP_(ENVIRONMENT, IDX + 1, _VOID_)
  
/* private functions */

static _NIL_TYPE_ exit_loop(_NIL_TYPE_)
 { SES_TAB[SES_IDX].res = _PICO_DONE_;
   SES_TAB[SES_IDX].dct = _DCT_;
   SES_TAB[SES_IDX].esc = _ESC_;
   _stk_zap_EXP_();
   _stk_zap_CNT_();
   longjmp(SES_TAB[SES_IDX].exi, 1); }

/* public functions */

_NIL_TYPE_ _accept_(_NIL_TYPE_)
 { SES_TAB[SES_IDX].res = _DO_ACCEPT_;
   longjmp(SES_TAB[SES_IDX].exi, 1); }

_NIL_TYPE_ _load_(const _STR_TYPE_ str)
 { SES_TAB[SES_IDX].res = _DO_LOAD_;
   STATUS = DISABLED;
   _PICO_MESSAGE_(SES_TAB[SES_IDX].ses, str);
   STATUS = ENABLED;
   longjmp(SES_TAB[SES_IDX].exi, 1); }

_NIL_TYPE_ _error_(const _RES_TYPE_ err)
 { SES_TAB[SES_IDX].res = err;
   _DCT_ = SES_TAB[SES_IDX].dct;
   _ESC_ = SES_TAB[SES_IDX].esc;
   CTX_INITIALISE(SES_IDX, _DCT_);
   CTX_RESTORE(SES_IDX);
   longjmp(SES_TAB[SES_IDX].exi, 1); }

_NIL_TYPE_ _reclaim_(const _UNS_TYPE_ mrg)
 { STATUS = DISABLED;
   _PICO_RECLAIM_(_RECLAIM_YES_);
   CTX_CAPTURE(SES_IDX);
   _mem_reclaim_(mrg); 
   CTX_RESTORE(SES_IDX); 
   GLOBAL = _ag_get_TAB_EXP_(ROOT, GLOBAL_ROOT);
   _NAMES_ = _ag_get_TAB_EXP_(ROOT, NAMES_ROOT);
   ENVIRONMENT = _ag_get_TAB_EXP_(ROOT, ENVIRONMENT_ROOT);
   _nat_reset_();
   _PICO_RECLAIM_(_RECLAIM_NO_);
   STATUS = ENABLED; }

_NIL_TYPE_ _error_str_(const _RES_TYPE_ err,
                       const _STR_TYPE_ str)
 { STATUS = DISABLED;
   _PICO_MESSAGE_(SES_TAB[SES_IDX].ses, str);
   STATUS = ENABLED;
   _error_(err); }

_NIL_TYPE_ _error_msg_(const _RES_TYPE_ err,
                       const _EXP_TYPE_ txt)
 { _error_str_(err, _ag_get_TXT_(txt)); }
 
_NIL_TYPE_ _print_(const _STR_TYPE_ str)
 { _ESC_TYPE_ esc;
   STATUS = DISABLED;
   esc = _PICO_PRINT_(SES_TAB[SES_IDX].ses, str);
   STATUS = ENABLED;
   if (esc == _ESCAPE_YES_)
     { SES_TAB[SES_IDX].res = _DO_ESCAPE_;
       longjmp(SES_TAB[SES_IDX].exi, 1); }}

_NIL_TYPE_ _mark_(const _POS_TYPE_ start,
                  const _POS_TYPE_ stop)
 { STATUS = DISABLED;
   _PICO_MARK_(SES_TAB[SES_IDX].ses, start, stop);
   STATUS = ENABLED; }

_NIL_TYPE_ _escape_(_NIL_TYPE_)
 { _ESC_TYPE_ esc;
   STATUS = DISABLED;
   esc = _PICO_ESCAPE_(SES_TAB[SES_IDX].ses);
   STATUS = ENABLED;
   if (esc == _ESCAPE_YES_)
     { SES_TAB[SES_IDX].res = _DO_ESCAPE_;
       longjmp(SES_TAB[SES_IDX].exi, 1); }
   if (_ag_is_VOI_(_ESC_))
     return;
   _nat_interrupt_(); }

_NIL_TYPE_ _display_(const _STR_TYPE_ str)
 { _ESC_TYPE_ esc;
   STATUS = DISABLED;
   esc = _PICO_DISPLAY_(SES_TAB[SES_IDX].ses, str);
   STATUS = ENABLED;
   if (esc == _ESCAPE_YES_)
     { SES_TAB[SES_IDX].res = _DO_ESCAPE_;
       CTX_CAPTURE(SES_IDX);
       longjmp(SES_TAB[SES_IDX].exi, 1); }}

/* debug functions */

#ifndef NDEBUG

_EXP_TYPE_ CHK_AGR(const _EXP_TYPE_ exp,
                   const _TAG_TYPE_ tag)
 { if (_ag_get_TAG_(exp) != tag)
     _error_(_AGR_ERROR_);
   return exp; }

#endif

/* exported functions */

_RES_TYPE_ _PICO_INIT_(const _ADR_TYPE_ adr,
                       const _SIZ_TYPE_ siz)
 { _SIZ_TYPE_ max = siz/_EXP_SIZE_;
   assert(sizeof(long) == 4);
   assert(sizeof(double) == 8);
   if (max < _GLOBAL_SIZE_)
     return _MEM_ERROR_;
   _mem_setup_(adr, max);
   ROOT = _ag_make_TAB_(ROOT_SIZE);
   ENVIRONMENT = _ag_make_TAB_(_MAX_SES_);
   for (SES_IDX = 0 ; SES_IDX < _MAX_SES_ ; SES_IDX++)
     { SES_TAB[SES_IDX].ses = -1; /* zero gave problems
				     in session zero -- DVD */
       CTX_VOID(SES_IDX); }
   _env_setup_((_SIZ_TYPE_)(max*_NAM_FRACT_));
   GLOBAL = _nat_install_(); 
   _ag_set_TAB_EXP_(ROOT, GLOBAL_ROOT, GLOBAL);
   _ag_set_TAB_EXP_(ROOT, NAMES_ROOT, _NAMES_);
   _ag_set_TAB_EXP_(ROOT, ENVIRONMENT_ROOT, ENVIRONMENT);
   _STK_MAX_ = (_UNS_TYPE_)(max*_STK_FRACT_);
   STATUS = ENABLED; 
   return _PICO_DONE_; }

_RES_TYPE_ _PICO_SESSION_(const _SES_TYPE_ ses)
 { static _BYT_TYPE_ idx;
   if (STATUS == NO_INIT)
     return _CTL_ERROR_;
   for (idx = 0 ; idx < _MAX_SES_ ; idx++)
     if (SES_TAB[idx].ses == ses)
       return _DPS_ERROR_;
   for (idx = 0 ; idx < _MAX_SES_ ; idx++)
     if (SES_TAB[idx].ses == -1) /* zero problem again -- DVD */
       { SES_TAB[idx].ses = ses;
         SES_TAB[idx].res = _PICO_DONE_;
         SES_TAB[idx].dct = GLOBAL;
         SES_TAB[idx].esc = _VOID_;
         CTX_INITIALISE(idx, GLOBAL);    
         return _PICO_DONE_; }
   return _TMS_ERROR_; }
   
_RES_TYPE_ _PICO_DO_(const _SES_TYPE_ ses,
                     const _STR_TYPE_ str)
 { if (STATUS != ENABLED)
     return _CTL_ERROR_;
   for (SES_IDX = 0 ; SES_IDX < _MAX_SES_ ; SES_IDX++)
     if (SES_TAB[SES_IDX].ses == ses)
       { CTX_RESTORE(SES_IDX);
         _stk_claim_();
         _mem_claim_STR_(str);
         _stk_push_EXP_(_ag_make_TXT_(str));         
         _stk_push_EXP_(_VOID_);  
         _stk_push_CNT_(exit_loop);
         _stk_push_CNT_(_print_EXP_);
         _stk_push_CNT_(_eval_MAI_); /* changed */
         _stk_push_CNT_(_read_EXP_);
         _ESC_ = SES_TAB[SES_IDX].esc;
         if (setjmp(SES_TAB[SES_IDX].exi) == 0) 
           _stk_loop_();
         CTX_CAPTURE(SES_IDX); 
         return SES_TAB[SES_IDX].res; }
   return _SNA_ERROR_; }

_RES_TYPE_ _PICO_ACCEPT_(const _SES_TYPE_ ses,
                         const _STR_TYPE_ str)
 { if (STATUS != ENABLED)
     return _CTL_ERROR_;
   for (SES_IDX = 0 ; SES_IDX < _MAX_SES_ ; SES_IDX++)
     if (SES_TAB[SES_IDX].ses == ses)
       { if (SES_TAB[SES_IDX].res != _DO_ACCEPT_)
           return _CTL_ERROR_;
         CTX_RESTORE(SES_IDX);
         _stk_claim_();
         _mem_claim_STR_(str);
         _stk_push_EXP_(_ag_make_TXT_(str)); 
         _ESC_ = SES_TAB[SES_IDX].esc;        
         if (setjmp(SES_TAB[SES_IDX].exi) == 0) 
           _stk_loop_();
         CTX_CAPTURE(SES_IDX);
         return SES_TAB[SES_IDX].res; }
   return _SNA_ERROR_; }

_RES_TYPE_ _PICO_LOAD_(const _SES_TYPE_ ses,
                       const _STR_TYPE_ str)
 { if (STATUS != ENABLED)
     return _CTL_ERROR_;
   for (SES_IDX = 0 ; SES_IDX < _MAX_SES_ ; SES_IDX++)
     if (SES_TAB[SES_IDX].ses == ses)
       { if (SES_TAB[SES_IDX].res != _DO_LOAD_)
           return _CTL_ERROR_;
         CTX_RESTORE(SES_IDX);
         _stk_claim_();
         _mem_claim_STR_(str);
         _stk_push_EXP_(_ag_make_TXT_(str));         
         _stk_push_EXP_(_VOID_);  
         _stk_push_CNT_(_print_EXP_);
         _stk_push_CNT_(_eval_EXP_);
         _stk_push_CNT_(_read_EXP_);
         _ESC_ = SES_TAB[SES_IDX].esc;
         if (setjmp(SES_TAB[SES_IDX].exi) == 0) 
           _stk_loop_();
         CTX_CAPTURE(SES_IDX);
         return SES_TAB[SES_IDX].res; }
   return _SNA_ERROR_; }

_RES_TYPE_ _PICO_CONTINUE_(const _SES_TYPE_ ses)
 { if (STATUS != ENABLED)
     return _CTL_ERROR_;
   for (SES_IDX = 0 ; SES_IDX < _MAX_SES_ ; SES_IDX++)
     if (SES_TAB[SES_IDX].ses == ses)
       { if (SES_TAB[SES_IDX].res != _DO_ESCAPE_)
           return _CTL_ERROR_;
         CTX_RESTORE(SES_IDX);
         _ESC_ = SES_TAB[SES_IDX].esc;
         if (setjmp(SES_TAB[SES_IDX].exi) == 0) 
           _stk_loop_();
         CTX_CAPTURE(SES_IDX);
         return SES_TAB[SES_IDX].res; }
   return _SNA_ERROR_; }         

_RES_TYPE_ _PICO_KILL_(const _SES_TYPE_ ses)
 { static _BYT_TYPE_ idx;
   if (STATUS == NO_INIT)
     return _CTL_ERROR_;
   for (idx = 0 ; idx < _MAX_SES_ ; idx++)
     if (SES_TAB[idx].ses == ses)
       { SES_TAB[idx].ses = -1; /* instead of zero -- DVD */
         CTX_VOID(idx);
         return _PICO_DONE_; }
   return _SNA_ERROR_; }
