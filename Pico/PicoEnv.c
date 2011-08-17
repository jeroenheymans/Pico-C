/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*            Environments           */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/*                                                                        */
/*    _stk_poke_CNT_(CNT)    =>   stack[_CNT_tos_] = CNT                  */
/*    _stk_push_CNT_(CNT)    =>   stack[--_CNT_tos_] = CNT                */
/*    _stk_peek_CNT_(CNT)    =>   stack[_CNT_tos_]                        */
/*    _stk_pop_CNT_ (   )    =>   stack[_CNT_tos_--]                      */
/*    _stk_zap_CNT_ (   )    =>   _CNT_tos_++                             */
/*                                                                        */
/*    _stk_poke_EXP_(EXP)    =>   stack[_EXP_tos_] = EXP                  */
/*    _stk_push_EXP_(EXP)    =>   stack[++_EXP_tos_] = EXP                */
/*    _stk_peek_EXP_(EXP)    =>   stack[_EXP_tos_]                        */
/*    _stk_pop_EXP_ (   )    =>   stack[_EXP_tos_--]                      */
/*    _stk_zap_EXP_ (   )    =>   _EXP_tos_--                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoNat.h"
#include "PicoEnv.h"

/* private variables */

static _SIZ_TYPE_ DCT_top = 1;
static _SIZ_TYPE_ DCT_siz = 0;

/* public variables */

_EXP_TYPE_ _DCT_;
_UNS_TYPE_ _CNT_;
_UNS_TYPE_ _EXP_;
_EXP_TYPE_ _STK_;
                           
/* public functions */

_NIL_TYPE_ _env_setup_(const _SIZ_TYPE_ siz)
 { _SIZ_TYPE_ idx;
   _NAMES_ = _ag_make_TAB_(siz);
   DCT_top = 1;
   DCT_siz = siz; 
   for (idx = 1; idx <= DCT_siz; idx++)
     _ag_set_TAB_EXP_(_NAMES_, idx, _VOID_); }
  
_EXP_TYPE_ _env_make_NAM_(const _STR_TYPE_ str)
 { _SIZ_TYPE_ idx;
   _EXP_TYPE_ nam;
   for (idx = 1; idx < DCT_top; idx++)
     { nam = _ag_get_TAB_EXP_(_NAMES_, idx);
       if (!strcmp(str, _ag_get_TXT_(nam)))
         return nam; }
   if (DCT_top > DCT_siz)
     _error_(_DCT_ERROR_);
   nam = _ag_make_TXT_(str);
   _ag_set_TAB_EXP_(_NAMES_, DCT_top++, nam);
   return nam; }
   
_EXP_TYPE_ _env_initialise_(const _EXP_TYPE_ dct)
 { _EXP_TYPE_ env, top, stk;
   _mem_claim_SIZ_(_STK_INIT_);
   env = _ag_make_ENV_();
   stk = _ag_make_TAB_(_STK_INIT_);
   top = _ag_make_NBR_(_STK_INIT_ + 1);
   _ag_set_ENV_DCT_(env, dct);
   _ag_set_ENV_BOT_(env, _ZERO_);
   _ag_set_ENV_TOP_(env, top);
   _ag_set_ENV_TAB_(env, stk);
   return env; }

_NIL_TYPE_ _env_capture_(const _EXP_TYPE_ env)
 { _EXP_TYPE_ bot, top;
   _UNS_TYPE_ adr, lwn, upn;
   adr = (_UNS_TYPE_)_mem_cast_raw_(_STK_, _TAB_TAG_);
   lwn = 1 + (_EXP_ - adr)/_EXP_SIZE_;
   upn = 1 + (_CNT_ - adr)/_EXP_SIZE_;
   bot = _ag_make_NBU_(lwn);                  
   top = _ag_make_NBU_(upn);                  
   _ag_set_ENV_DCT_(env, _DCT_); 
   _ag_set_ENV_BOT_(env, bot);
   _ag_set_ENV_TOP_(env, top);
   _ag_set_ENV_TAB_(env, _STK_); }

_NIL_TYPE_ _env_restore_(const _EXP_TYPE_ env)
 { _EXP_TYPE_ bot, top;
   _UNS_TYPE_ adr, lwn, upn;
   _DCT_ = _ag_get_ENV_DCT_(env); 
   bot   = _ag_get_ENV_BOT_(env);
   top   = _ag_get_ENV_TOP_(env);
   _STK_ = _ag_get_ENV_TAB_(env);
   lwn   = _ag_get_NBU_(bot);
   upn   = _ag_get_NBU_(top);
   adr   = (_UNS_TYPE_)_mem_cast_raw_(_STK_, _TAB_TAG_);
   _EXP_ = adr + (lwn - 1)*_EXP_SIZE_; 
   _CNT_ = adr + (upn - 1)*_EXP_SIZE_; }

_NIL_TYPE_ _env_expand_(_NIL_TYPE_)
 { _EXP_TYPE_ exp, stk;
   _UNS_TYPE_ adr, idx, lwn, siz, upn, xsz;
   siz = _ag_get_TAB_SIZ_(_STK_); 
   xsz = 2*siz;
   if (xsz > _STK_MAX_)
     _error_(_STK_ERROR_); 
   _mem_claim_SIZ_(xsz);
   adr = (_UNS_TYPE_)_mem_cast_raw_(_STK_, _TAB_TAG_);
   lwn = 1 + (_EXP_ - adr)/_EXP_SIZE_;
   upn = 1 + (_CNT_ - adr)/_EXP_SIZE_;
   stk = _ag_make_TAB_(xsz);
   for (idx = 1 ; idx <= lwn ; idx++)
     { exp = _ag_get_TAB_EXP_(_STK_, idx);
       _ag_set_TAB_EXP_(stk, idx, exp); }
   for (idx = siz ; idx >= upn ; idx--)
     { exp = _ag_get_TAB_EXP_(_STK_, idx);
       _ag_set_TAB_EXP_(stk, xsz--, exp); }
   for ( ; xsz > lwn ; xsz--)
     _ag_set_TAB_EXP_(stk, xsz, _VOID_);
   adr   = (_UNS_TYPE_)_mem_cast_raw_(stk, _TAB_TAG_);
   _EXP_ = adr + (lwn - 1)*_EXP_SIZE_; 
   _CNT_ = adr + (upn + siz - 1)*_EXP_SIZE_; 
   _STK_ = stk; }

_NIL_TYPE_ _env_save_(const _EXP_TYPE_ env)
 { _EXP_TYPE_ bot, exp, stk, top; 
   _UNS_TYPE_ adr, idx, lwn, siz, upn;
   siz = _ag_get_TAB_SIZ_(_STK_);
   // _mem_claim_SIZ_(siz); // dvd: would corrupt, cfr CLL
   adr = (_UNS_TYPE_)_mem_cast_raw_(_STK_, _TAB_TAG_);
   lwn = 1 + (_EXP_ - adr)/_EXP_SIZE_;
   upn = 1 + (_CNT_ - adr)/_EXP_SIZE_;
   bot = _ag_make_NBU_(lwn);                  
   top = _ag_make_NBU_(upn);                  
   stk = _ag_make_TAB_(siz);
   for (idx = 1 ; idx <= siz ; idx++)
     { exp = _ag_get_TAB_EXP_(_STK_, idx);
       _ag_set_TAB_EXP_(stk, idx, exp); }
   _ag_set_ENV_DCT_(env, _DCT_);
   _ag_set_ENV_BOT_(env, bot);
   _ag_set_ENV_TOP_(env, top);
   _ag_set_ENV_TAB_(env, stk); }
   
_NIL_TYPE_ _env_load_(const _EXP_TYPE_ env)
 { _EXP_TYPE_ bot, exp, stk, top; 
   _UNS_TYPE_ adr, idx, lwn, siz, upn;
   siz = _ag_get_TAB_SIZ_(_STK_);
   // _mem_claim_SIZ_(siz); // dvd: would corrupt, cfr COX
   _DCT_ = _ag_get_ENV_DCT_(env); 
   bot   = _ag_get_ENV_BOT_(env);
   top   = _ag_get_ENV_TOP_(env);
   stk   = _ag_get_ENV_TAB_(env);
   _STK_ = _ag_make_TAB_(siz);
   for (idx = 1 ; idx <= siz ; idx++)
     { exp = _ag_get_TAB_EXP_(stk, idx);
       _ag_set_TAB_EXP_(_STK_, idx, exp); }
   lwn   = _ag_get_NBU_(bot);
   upn   = _ag_get_NBU_(top);
   adr   = (_UNS_TYPE_)_mem_cast_raw_(_STK_, _TAB_TAG_);
   _EXP_ = adr + (lwn - 1)*_EXP_SIZE_; 
   _CNT_ = adr + (upn - 1)*_EXP_SIZE_; }
