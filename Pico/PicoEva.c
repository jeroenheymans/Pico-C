/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*            Evaluation             */
/*-----------------------------------*/

#include "Pico.h"
#include "PicoMai.h"
#include "PicoEnv.h"
#include "PicoMem.h"
#include "PicoNat.h"
#include "PicoEva.h"
#include "PicoSch.h"

#include <stdio.h>

/* private constants */

#define CAL _eval_CAL_   
#define EXP _eval_EXP_   
#define NAT _eval_NAT_   

/* private prototypes */

static _NIL_TYPE_ APL(_NIL_TYPE_);  
static _NIL_TYPE_ ASS(_NIL_TYPE_); 
static _NIL_TYPE_ ATA(_NIL_TYPE_); 
static _NIL_TYPE_ ATV(_NIL_TYPE_); 
static _NIL_TYPE_ BND(_NIL_TYPE_);
static _NIL_TYPE_ CHG(_NIL_TYPE_);
static _NIL_TYPE_ DEF(_NIL_TYPE_); 
static _NIL_TYPE_ IDX(_NIL_TYPE_); 
static _NIL_TYPE_ INI(_NIL_TYPE_); 
static _NIL_TYPE_ NYI(_NIL_TYPE_); 
static _NIL_TYPE_ REF(_NIL_TYPE_); 
static _NIL_TYPE_ RET(_NIL_TYPE_); 
static _NIL_TYPE_ RPL(_NIL_TYPE_); 
static _NIL_TYPE_ SCH(_NIL_TYPE_); 
static _NIL_TYPE_ SET(_NIL_TYPE_); 
static _NIL_TYPE_ SLF(_NIL_TYPE_); 
static _NIL_TYPE_ SWI(_NIL_TYPE_); 
static _NIL_TYPE_ SWP(_NIL_TYPE_); 
static _NIL_TYPE_ TBL(_NIL_TYPE_); 
static _NIL_TYPE_ THA(_NIL_TYPE_);
static _NIL_TYPE_ THa(_NIL_TYPE_);
static _NIL_TYPE_ THB(_NIL_TYPE_);
static _NIL_TYPE_ THE(_NIL_TYPE_);
static _NIL_TYPE_ THF(_NIL_TYPE_);
static _NIL_TYPE_ THQ(_NIL_TYPE_);
static _NIL_TYPE_ THq(_NIL_TYPE_);
static _NIL_TYPE_ THR(_NIL_TYPE_);
static _NIL_TYPE_ VAR(_NIL_TYPE_); 
static _NIL_TYPE_ ZEX(_NIL_TYPE_);

/* private variables */ 

static const _BYT_TYPE_ TAB_tab[] =
   { 0,    /* VOI */
     1,    /* NAT */ 
     0,    /* FRC */
     0,    /* TXT */
     1,    /* TAB */
     1,    /* FUN */
     1,    /* VAR */
     1,    /* APL */
     1,    /* TBL */
     1,    /* DEF */
     1,    /* SET */
     1,    /* DCT */
     1,    /* ENV */
     0,    /* NYI */
     0,    /* NYI */
     0,    /* NYI */
     0,    /* NBR */
     0,    /* THA */
     0,    /* THQ */
     0,    /* THR */
     0 };  /* TID */
     
static const _CNT_TYPE_ CNT_tab[] = 
   { SLF,    /* VOI */
     SLF,    /* NAT */ 
     SLF,    /* FRC */
     SLF,    /* TXT */
     SLF,    /* TAB */
     SLF,    /* FUN */
     VAR,    /* VAR */
     APL,    /* APL */
     TBL,    /* TBL */
     DEF,    /* DEF */
     SET,    /* SET */
     SLF,    /* DCT */
     SLF,    /* ENV */
     NYI,    /* NYI */
     NYI,    /* NYI */
     NYI,    /* NYI */
     SLF,    /* NBR */
     THA,    /* THA */
     THQ,    /* THQ */
     THR,    /* THR */
     NYI };  /* TID */
     
static const _UNS_TYPE_ max = 5;
static _UNS_TYPE_ eval_counter;
 
/* private functions */

/*------------------------------------------------------------------------*/
/*  NYI                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... NYI] -> [... ... ... ... ... ERR] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NYI(_NIL_TYPE_)
 { _error_(_AGR_ERROR_); }
   
/*------------------------------------------------------------------------*/
/*  APL                                                                   */
/*     expr-stack: [... ... ... ... ... APL] -> [... ... ... ... FUN ARG] */
/*     cont-stack: [... ... ... ... ... APL] -> [... ... ... ... ... CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... APL] -> [... ... ... ... FUN ARG] */
/*     cont-stack: [... ... ... ... ... APL] -> [... ... ... ... CAL EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... APL] -> [... ... ... ... NBR ARG] */
/*     cont-stack: [... ... ... ... ... APL] -> [... ... ... ... ... NAT] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... APL] -> [... ... ... ... NBR ARG] */
/*     cont-stack: [... ... ... ... ... APL] -> [... ... ... ... NAT EXP] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ APL(_NIL_TYPE_)
 { _EXP_TYPE_ apl, arg, dct, fun, nam, nbr;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _stk_peek_EXP_(apl);
   nam = _ag_get_APL_NAM_(apl);
   arg = _ag_get_APL_ARG_(apl);
   _dct_locate_(nam, dct, _DCT_);
   fun = _ag_get_DCT_VAL_(dct);
   tag = _ag_get_TAG_(fun);
   switch (tag)
    { case _FUN_TAG_:
        _stk_poke_EXP_(fun);
        _stk_poke_CNT_(CAL);
        break;
      case _NAT_TAG_:
        nbr = _ag_get_NAT_NBR_(fun);
        _stk_poke_EXP_(nbr);
        _stk_poke_CNT_(NAT);
        break; 
      default:
        _error_msg_(_NAF_ERROR_, nam); }
   _stk_push_EXP_(arg);
   tag = _ag_get_TAG_(arg);
   if (tag != _TAB_TAG_)  
     _stk_push_CNT_(EXP); }

/*------------------------------------------------------------------------*/
/*  ASS                                                                   */
/*     expr-stack: [... ... ... ... DCT VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ASS] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ ASS(_NIL_TYPE_)
 { _EXP_TYPE_ dct, val;
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(dct);
   _ag_set_DCT_VAL_(dct, val);
   _ag_set_DCT_DCT_(dct, _DCT_);
   _DCT_ = dct; 
   _stk_poke_EXP_(val); 
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  ATA                                                                   */
/*     expr-stack: [EXP DCT ARG TAB NBR APL] -> [EXP DCT ARG TAB NBR APL] */
/*     cont-stack: [... ... ... ... ... ATA] -> [... ... ... ... ... ATA] */
/*                                                                        */
/*     expr-stack: [EXP DCT ARG TAB NBR APL] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... ATA] -> [... ... ... ... RET EXP] */
/*                                                                        */
/*     expr-stack: [EXP DCT ARG TAB NBR APL] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... ATA] -> [... ... ... ... ... EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ ATA(_NIL_TYPE_)
 { _EXP_TYPE_ act, apl, arg, dct, exp, fun, nam, nbr, par, tab;
   _CNT_TYPE_ cnt;
   _UNS_TYPE_ ctr, siz;
   _mem_claim_();
   fun = _ag_make_FUN_();
   _stk_pop_EXP_(apl);
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(tab);
   _stk_pop_EXP_(arg);
   _stk_peek_EXP_(dct);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   act = _ag_get_TAB_EXP_(arg, ctr);
   nam = _ag_get_APL_NAM_(apl);
   par = _ag_get_APL_ARG_(apl);
   _ag_set_FUN_NAM_(fun, nam);
   _ag_set_FUN_ARG_(fun, par);
   _ag_set_FUN_EXP_(fun, act);
   _ag_set_FUN_DCT_(fun, dct);
   _ag_set_TAB_EXP_(tab, ctr, fun);
   if (ctr < siz)
     { _stk_push_EXP_(arg);
       _stk_push_EXP_(tab);
       nbr = _ag_succ_NBR_(nbr);
       _stk_push_EXP_(nbr);
       _stk_push_EXP_(apl); }
   else
     { _ag_set_DCT_VAL_(dct, tab);
       _stk_zap_EXP_();
       _stk_zap_CNT_();
       _stk_peek_CNT_(cnt);
       if (cnt != RET)
         { _stk_peek_EXP_(exp);
           _stk_poke_EXP_(_DCT_);
           _stk_push_EXP_(exp); 
           _stk_push_CNT_(RET); }
       _stk_push_CNT_(EXP); 
       _DCT_ = dct; }}

/*------------------------------------------------------------------------*/
/*  ATV                                                                   */
/*     expr-stack: [EXP DCT ARG TAB NBR VAL] -> [EXP DCT ARG TAB NBR EXP] */
/*     cont-stack: [... ... ... ... ... ATV] -> [... ... ... ... ATV EXP] */
/*                                                                        */
/*     expr-stack: [EXP DCT ARG TAB NBR VAL] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... ATV] -> [... ... ... ... RET EXP] */
/*                                                                        */
/*     expr-stack: [EXP DCT ARG TAB NBR VAL] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... ATV] -> [... ... ... ... ... EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ ATV(_NIL_TYPE_)
 { _EXP_TYPE_ act, arg, dct, exp, nbr, tab, val;
   _CNT_TYPE_ cnt;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(tab);
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   _ag_set_TAB_EXP_(tab, ctr, val);
   if (ctr < siz)
     { act = _ag_get_TAB_EXP_(arg, ctr+1);
       _stk_push_EXP_(tab);
       nbr = _ag_succ_NBR_(nbr);
       _stk_push_EXP_(nbr);
       _stk_push_EXP_(act);
       _stk_push_CNT_(EXP); }
   else
     { _stk_zap_EXP_();
       _stk_pop_EXP_(dct);
       _ag_set_DCT_VAL_(dct, tab);
       _stk_zap_CNT_();
       _stk_peek_CNT_(cnt);
       if (cnt != RET)
         { _stk_peek_EXP_(exp);
           _stk_poke_EXP_(_DCT_);
           _stk_push_EXP_(exp); 
           _stk_push_CNT_(RET); }
       _stk_push_CNT_(EXP); 
       _DCT_ = dct; }}

/*------------------------------------------------------------------------*/
/*  BND                                                                   */
/*     expr-stack: [EXP PAR ARG NBR DCT VAL] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... BND] -> [... ... ... ... RET EXP] */
/*                                                                        */
/*     expr-stack: [EXP PAR ARG NBR DCT VAL] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... BND] -> [... ... ... ... ... EXP] */
/*                                                                        */
/*     expr-stack: [EXP PAR ARG NBR DCT VAL] -> [EXP PAR ARG NBR DCT EXP] */
/*     cont-stack: [... ... ... ... ... BND] -> [... ... ... ... BND EXP] */
/*                                                                        */
/*     expr-stack: [EXP PAR ARG NBR DCT VAL] -> [EXP PAR ARG NBR DCT FUN] */
/*     cont-stack: [... ... ... ... ... BND] -> [... ... ... ... ... BND] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ BND(_NIL_TYPE_)
 { _EXP_TYPE_ act, arg, dct, exp, fun, frm, nam, nbr, par, val, xdc;
   _CNT_TYPE_ cnt;
   _TAG_TYPE_ tag;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _mem_claim_();
   _stk_pop_EXP_(val);
   _stk_pop_EXP_(dct);
   _ag_set_DCT_VAL_(dct, val);
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   if (ctr == siz)
     { _stk_zap_EXP_();
       _stk_zap_CNT_();
       _stk_peek_CNT_(cnt);
       if (cnt != RET)
         { _stk_peek_EXP_(exp);
           _stk_poke_EXP_(_DCT_);
           _stk_push_EXP_(exp); 
           _stk_push_CNT_(RET); }
       _stk_push_CNT_(EXP); 
       _DCT_ = dct; }
   else
     { _stk_peek_EXP_(par);
       frm = _ag_get_TAB_EXP_(par, ++ctr);
       act = _ag_get_TAB_EXP_(arg, ctr);
       tag = _ag_get_TAG_(frm);
       _stk_push_EXP_(arg); 
       nbr = _ag_succ_NBR_(nbr);
       _stk_push_EXP_(nbr); 
       xdc = _ag_make_DCT_();
       _stk_push_EXP_(xdc); 
       _ag_set_DCT_DCT_(xdc, dct);
       switch (tag)
        { case _VAR_TAG_:          
            nam = _ag_get_VAR_NAM_(frm);    
            _ag_set_DCT_NAM_(xdc, nam);
            _stk_push_EXP_(act);
            _stk_push_CNT_(EXP);
            break;
          case _APL_TAG_:
            fun = _ag_make_FUN_();
            nam = _ag_get_APL_NAM_(frm);
            arg = _ag_get_APL_ARG_(frm);
            _ag_set_DCT_NAM_(xdc, nam);
            _ag_set_FUN_NAM_(fun, nam);
            _ag_set_FUN_ARG_(fun, arg);
            _ag_set_FUN_EXP_(fun, act);
            _ag_set_FUN_DCT_(fun, _DCT_);
            _stk_push_EXP_(fun);
             break;
          default:
            _error_(_IPM_ERROR_); }}}
   
/*------------------------------------------------------------------------*/
/*  CHG                                                                   */
/*     expr-stack: [... ... ... ... DCT VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... CHG] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ CHG(_NIL_TYPE_)
 { _EXP_TYPE_ dct, val;
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(dct);
   _ag_set_DCT_VAL_(dct, val);
   _stk_poke_EXP_(val); 
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  DEF                                                                   */
/*     expr-stack: [... ... ... ... ... DEF] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... DEF] -> [... ... ... ... ASS EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... DEF] -> [... ... ... ... ... FUN] */
/*     cont-stack: [... ... ... ... ... DEF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... DEF] -> [... ... ... DCT EXP IDX] */
/*     cont-stack: [... ... ... ... ... DEF] -> [... ... ... ... IDX EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ DEF(_NIL_TYPE_)
 { _EXP_TYPE_ arg, dct, def, exp, fun, idx, inv, nam;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _mem_claim_();
   dct = _ag_make_DCT_();
   _stk_peek_EXP_(def);
   inv = _ag_get_DEF_INV_(def);
   exp = _ag_get_DEF_EXP_(def);
   tag = _ag_get_TAG_(inv);
   switch (tag)
    { case _VAR_TAG_:
        nam = _ag_get_VAR_NAM_(inv);
        _ag_set_DCT_NAM_(dct, nam);
        _stk_poke_EXP_(dct);
        _stk_push_EXP_(exp);
        _stk_poke_CNT_(ASS);
        _stk_push_CNT_(EXP); 
        break;
      case _APL_TAG_:
        fun = _ag_make_FUN_();
        nam = _ag_get_APL_NAM_(inv);
        arg = _ag_get_APL_ARG_(inv);
        _ag_set_DCT_NAM_(dct, nam);
        _ag_set_DCT_VAL_(dct, fun);
        _ag_set_DCT_DCT_(dct, _DCT_);
        _DCT_ = dct; 
        _ag_set_FUN_NAM_(fun, nam);
        _ag_set_FUN_ARG_(fun, arg);
        _ag_set_FUN_EXP_(fun, exp);
        _ag_set_FUN_DCT_(fun, dct);
        _stk_poke_EXP_(fun); 
        _stk_zap_CNT_(); 
        break;
      case _TBL_TAG_:
        nam = _ag_get_TBL_NAM_(inv);
        idx = _ag_get_TBL_IDX_(inv);
        _ag_set_DCT_NAM_(dct, nam);
        _stk_poke_EXP_(dct);
        _stk_push_EXP_(exp);
        _stk_push_EXP_(idx);
        _stk_poke_CNT_(IDX);
        _stk_push_CNT_(EXP); 
        break; 
      default: 
        _error_(_AGR_ERROR_); }}
   
/*------------------------------------------------------------------------*/
/*  IDX                                                                   */
/*     expr-stack: [... ... ... DCT EXP NBR] -> [... DCT TAB EXP *1* EXP] */
/*     cont-stack: [... ... ... ... ... IDX] -> [... ... ... ... INI EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... DCT EXP NBR] -> [... ... ... ... ... *E*] */
/*     cont-stack: [... ... ... ... ... IDX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ IDX(_NIL_TYPE_)
 { _EXP_TYPE_ dct, exp, nbr, tab;
   _TAG_TYPE_ tag;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_pop_EXP_(nbr);
   tag = _ag_get_TAG_(nbr);
   if (tag == _NBR_TAG_) 
     { siz = _ag_get_NBU_(nbr);
       if (siz == 0) 
         { _stk_zap_EXP_();
           _stk_peek_EXP_(dct);
           _ag_set_DCT_VAL_(dct, _EMPTY_); 
				   _ag_set_DCT_DCT_(dct, _DCT_);
				   _DCT_ = dct; 
           _stk_poke_EXP_(_EMPTY_);
           _stk_zap_CNT_(); }
       else if (siz > 0)
         { _mem_claim_SIZ_(siz);
           tab = _ag_make_TAB_(siz);
           _stk_peek_EXP_(exp);
           _stk_poke_EXP_(tab);
           _stk_push_EXP_(exp);
           _stk_push_EXP_(_ONE_);
           _stk_push_EXP_(exp);
           _stk_poke_CNT_(INI);
           _stk_push_CNT_(EXP); }
	     else
	       _error_(_SIZ_ERROR_);}
   else
     _error_(_SIZ_ERROR_); }

/*------------------------------------------------------------------------*/
/*  INI                                                                   */
/*     expr-stack: [... DCT TAB EXP NBR VAL] -> [... DCT TAB EXP NBR EXP] */
/*     cont-stack: [... ... ... ... ... INI] -> [... ... ... ... INI EXP] */
/*                                                                        */
/*     expr-stack: [... DCT TAB EXP NBR VAL] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... INI] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ INI(_NIL_TYPE_)
 { _EXP_TYPE_ dct, exp, nbr, tab, val;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(tab);
   siz = _ag_get_TAB_SIZ_(tab);
   ctr = _ag_get_NBU_(nbr);
   _ag_set_TAB_EXP_(tab, ctr, val);
   if (ctr < siz)
     { nbr = _ag_succ_NBR_(nbr);
       _stk_push_EXP_(exp);
       _stk_push_EXP_(nbr);
       _stk_push_EXP_(exp);
       _stk_push_CNT_(EXP); }
   else
     { _stk_zap_EXP_();
       _stk_peek_EXP_(dct);
       _ag_set_DCT_VAL_(dct, tab); 
		   _ag_set_DCT_DCT_(dct, _DCT_);
		   _DCT_ = dct; 
		   _stk_poke_EXP_(tab);
       _stk_zap_CNT_(); }}
  
/*------------------------------------------------------------------------*/
/*  REF                                                                   */
/*     expr-stack: [... ... ... ... TAB NBR] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... REF] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ REF(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr, tab;
   _UNS_TYPE_ ctr, siz;
   _TAG_TYPE_ tag;
   _stk_pop_EXP_(nbr);
   _stk_peek_EXP_(tab);
   tag = _ag_get_TAG_(tab);
   if (TAB_tab[tag])
     { siz = _ag_get_TAB_SIZ_(tab);
       tag = _ag_get_TAG_(nbr);
       if (tag == _NBR_TAG_) 
         { ctr = _ag_get_NBU_(nbr);
           if ((ctr > 0) && (ctr <= siz))
             { exp = _ag_get_TAB_EXP_(tab, ctr);
               _stk_poke_EXP_(exp);
               _stk_zap_CNT_(); }
           else
             _error_(_RNG_ERROR_); }
       else
        _error_(_IIX_ERROR_); }
   else 
     _error_(_NAT_ERROR_); }

/*------------------------------------------------------------------------*/
/*  RET                                                                   */
/*     expr-stack: [... ... ... ... DCT VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... RET] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ RET(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(_DCT_);
   _stk_poke_EXP_(val);
   _stk_zap_CNT_(); 
   _ESCAPE_; }

/*------------------------------------------------------------------------*/
/*  RPL                                                                   */
/*     expr-stack: [... ... ... TAB VAL NBR] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... RPL] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ RPL(_NIL_TYPE_)
 { _EXP_TYPE_ nbr, tab, val;
   _UNS_TYPE_ ctr, siz;
   _TAG_TYPE_ tag;
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(tab);
   tag = _ag_get_TAG_(tab);
   if (TAB_tab[tag])
     { siz = _ag_get_TAB_SIZ_(tab);
       tag = _ag_get_TAG_(nbr);
       if (tag == _NBR_TAG_) 
         { ctr = _ag_get_NBU_(nbr);
           if ((ctr > 0) && (ctr <= siz))
             { _ag_set_TAB_EXP_(tab, ctr, val);
               _stk_zap_CNT_(); }
           else
             _error_(_RNG_ERROR_); }
       else
         _error_(_IIX_ERROR_); }
   else 
     _error_(_NAT_ERROR_); }

/*------------------------------------------------------------------------*/
/*  SET                                                                   */
/*     expr-stack: [... ... ... ... ... SET] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... SET] -> [... ... ... ... CHG EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... SET] -> [... ... ... ... ... FUN] */
/*     cont-stack: [... ... ... ... ... SET] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... SET] -> [... ... ... TAB IDX EXP] */
/*     cont-stack: [... ... ... ... ... SET] -> [... ... ... RPL SWP EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SET(_NIL_TYPE_)
 { _EXP_TYPE_ arg, dct, exp, fun, idx, inv, nam, set, tab;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _mem_claim_();
   _stk_peek_EXP_(set);
   inv = _ag_get_SET_INV_(set);
   exp = _ag_get_SET_EXP_(set);
   tag = _ag_get_TAG_(inv);
   switch (tag)
    { case _VAR_TAG_:
        nam = _ag_get_VAR_NAM_(inv);
        _dct_locate_(nam, dct, _DCT_);
        _stk_poke_EXP_(dct);
        _stk_push_EXP_(exp);
        _stk_poke_CNT_(CHG);
        _stk_push_CNT_(EXP); 
        break;
      case _APL_TAG_:
        fun = _ag_make_FUN_();
        inv = _ag_get_SET_INV_(set);
        nam = _ag_get_APL_NAM_(inv);
        arg = _ag_get_APL_ARG_(inv);
        _dct_locate_(nam, dct, _DCT_);
        _ag_set_DCT_VAL_(dct, fun);
        _ag_set_FUN_NAM_(fun, nam);
        _ag_set_FUN_ARG_(fun, arg);
        _ag_set_FUN_EXP_(fun, exp);
        _ag_set_FUN_DCT_(fun, _DCT_);
        _stk_poke_EXP_(fun); 
        _stk_zap_CNT_(); 
        break;
      case _TBL_TAG_:
        nam = _ag_get_TBL_NAM_(inv);
        idx = _ag_get_TBL_IDX_(inv);
        _dct_locate_(nam, dct, _DCT_);
        tab = _ag_get_DCT_VAL_(dct);
        _stk_poke_EXP_(tab);
        _stk_push_EXP_(idx);
        _stk_push_EXP_(exp);
        _stk_poke_CNT_(RPL);
        _stk_push_CNT_(SWP);    
        _stk_push_CNT_(EXP); 
        break; 
      default:
       _error_(_AGR_ERROR_); }}
        
/*------------------------------------------------------------------------*/
/*  SLF                                                                   */
/*     expr-stack: [... ... ... ... ... VOI] -> [... ... ... ... ... VOI] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... NAT] -> [... ... ... ... ... NAT] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... FRC] -> [... ... ... ... ... FRC] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... TXT] -> [... ... ... ... ... TXT] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... TAB] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... FUN] -> [... ... ... ... ... FUN] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... DCT] -> [... ... ... ... ... DCT] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ENV] -> [... ... ... ... ... ENV] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... NBR] -> [... ... ... ... ... NBR] */
/*     cont-stack: [... ... ... ... ... SLF] -> [... ... ... ... ... ...] */
/*                                                                        */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SLF(_NIL_TYPE_)
 { _stk_zap_CNT_(); }
 
/*------------------------------------------------------------------------*/
/*  SWI                                                                   */
/*     expr-stack: [... ... ... ... EXP EXP] -> [... ... ... ... EXP EXP] */
/*     cont-stack: [... ... ... ... ... SWI] -> [... ... ... ... ... EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SWI(_NIL_TYPE_)
 { _EXP_TYPE_ ex1, ex2;
   _stk_pop_EXP_(ex1);
   _stk_pop_EXP_(ex2);
   _stk_push_EXP_(ex1);
   _stk_push_EXP_(ex2);
   _stk_zap_CNT_(); }        
   
/*------------------------------------------------------------------------*/
/*  SWP                                                                   */
/*     expr-stack: [... ... ... TAB EXP VAL] -> [... ... ... TAB VAL EXP] */
/*     cont-stack: [... ... ... ... ... SWP] -> [... ... ... ... ... EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SWP(_NIL_TYPE_)
 { _EXP_TYPE_ exp, val; 
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(val);
   _stk_push_EXP_(exp);  
   _stk_poke_CNT_(EXP); } 

/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... ... TBL] -> [... ... ... ... TAB EXP] */
/*     cont-stack: [... ... ... ... ... TBL] -> [... ... ... ... REF EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TBL(_NIL_TYPE_)
 { _EXP_TYPE_ dct, idx, nam, tab, tbl;
   _stk_claim_();
   _stk_peek_EXP_(tbl);
   nam = _ag_get_TBL_NAM_(tbl);
   idx = _ag_get_TBL_IDX_(tbl);
   _dct_locate_(nam, dct, _DCT_);
   tab = _ag_get_DCT_VAL_(dct);
   _stk_poke_EXP_(tab);
   _stk_push_EXP_(idx);
   _stk_poke_CNT_(REF);
   _stk_push_CNT_(EXP); }

/*------------------------------------------------------------------------*/
/*  VAR                                                                   */
/*     expr-stack: [... ... ... ... ... VAR] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... VAR] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ VAR(_NIL_TYPE_)
 { _EXP_TYPE_ dct, nam, val, var;
   _stk_peek_EXP_(var);
   nam = _ag_get_VAR_NAM_(var);
   _dct_locate_(nam, dct, _DCT_);
   val = _ag_get_DCT_VAL_(dct);
   _stk_poke_EXP_(val);
   _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  SCH (scheduler, switch threads)                                       */
/*     expr-stack: [... ... ... ... *** TID] -> [... ... ... ... ... ***] */
/*     cont-stack: [... ... ... ... ... SCH] -> [... ... ... ... ... ***] */
/*------------------------------------------------------------------------*/ 
static _NIL_TYPE_ SCH(_NIL_TYPE_)
 { _EXP_TYPE_ scc, scn, thr, tid, nxt;
   _TAG_TYPE_ tag;
   _stk_pop_EXP_(tid);
   _stk_zap_CNT_();
   scc = _SCH_CURRENT_;
   tag = _ag_get_TAG_(tid);
   if (tag == _TID_TAG_)
      scn = _scheduler_find_(tid);
   else
      scn = _scheduler_next_();
   nxt = _ag_get_SCH_THR_(scn);
   thr = _ag_get_SCH_THR_(scc);
   if(!_mem_is_same_(thr, nxt))
     { _EXP_TYPE_ env = _ag_get_THR_ENV_(thr);
       _env_save_(env);
       _ag_set_THR_ENV_(thr, env);
       env = _ag_get_THR_ENV_(nxt);
       _env_load_(env);
       _SCH_CURRENT_ = scn; }
   _ESCAPE_; }
   
/*------------------------------------------------------------------------*/
/*  THA (thread-answer)                                                   */
/*     expr-stack: [... ... ... ... ... THA] -> [... ... THA INV 000 ARG] */
/*     cont-stack: [... ... ... ... ... THA] -> [... ... ... THa EXP THE] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THA(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, inv, nam, nta, tab, tha;
   _UNS_TYPE_ idx, siz;
   _stk_claim_();
   _stk_peek_EXP_(tha);
   _mem_claim_();
   inv = _ag_get_THA_INV_(tha);
   nam = _ag_get_THA_NAM_(tha);
   arg = _ag_get_THA_ARG_(tha);
   siz = _ag_get_TAB_SIZ_(arg);
   tab = _ag_make_TAB_(siz);
   for(idx = 1; idx <= siz; ++idx)
     { exp = _ag_get_TAB_EXP_(arg, idx);
       _ag_set_TAB_EXP_(tab, idx, exp); }
   nta = _ag_make_THA_();
   _ag_set_THA_INV_(nta, inv);
   _ag_set_THA_NAM_(nta, nam);
   _ag_set_THA_ARG_(nta, tab);
   _stk_poke_EXP_(nta);
   _stk_push_EXP_(inv);
   _stk_push_EXP_(_ZERO_);
   _stk_push_EXP_(tab);
   _stk_poke_CNT_(THa);
   _stk_push_CNT_(EXP);
   _stk_push_CNT_(THE); }

/*------------------------------------------------------------------------*/
/*  THa (thread answer)                                                   */
/*     expr-stack: [... ... ... ... THA TID] -> [... ... ... ... ... TID] */
/*     cont-stack: [... ... ... ... ... THa] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... THA TID] -> [... ... ... THA TID VOI] */
/*     cont-stack: [... ... ... ... ... THa] -> [... ... ... ... THa SCH] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THa(_NIL_TYPE_)
 { _EXP_TYPE_ tha, tid;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _stk_pop_EXP_(tid);
   _stk_peek_EXP_(tha);
   _stk_push_EXP_(tid);
   tag = _ag_get_TAG_(tid);
   if(tag == _TID_TAG_)
     { _EXP_TYPE_ arg, cev, nam, sch, thr, env;
       _BYT_TYPE_ res;
       nam = _ag_get_THA_NAM_(tha);
       arg = _ag_get_THA_ARG_(tha);
       sch = _scheduler_find_(tid);
       thr = _ag_get_SCH_THR_(sch);
       env = _ag_get_THR_ENV_(thr);
       _CNT_TYPE_ thq_top;
       _env_save_(cev);
       _env_load_(env);
       _stk_claim_();
       _stk_peek_CNT_(thq_top);
       if(thq_top == THq)
         { _EXP_TYPE_ cur_idf, cur_thr, thq_idf, thq_tid;
           _stk_peek_EXP_(thq_tid);
           thq_idf = _ag_get_TID_TID_(thq_tid);
           cur_thr = _ag_get_SCH_THR_(_SCH_CURRENT_);
           cur_idf = _ag_get_THR_TID_(cur_thr);
           if(_mem_is_same_(cur_idf, thq_idf))
             { _EXP_TYPE_ thq, thq_nam;
               _stk_zap_EXP_();
               _stk_pop_EXP_(thq);
               thq_nam = _ag_get_THQ_NAM_(thq);
               if(_mem_is_same_(nam, thq_nam))
                 { _EXP_TYPE_ par = _ag_get_THQ_ARG_(thq);
                   _stk_push_EXP_(thq_tid);
                   _stk_push_EXP_(par);
                   _stk_push_EXP_(arg);
                   _stk_push_EXP_(_ZERO_);
                   _stk_poke_CNT_(THB);
                   res = 0; }
               else // messages don't match
                 res = 1; }
             else // already waiting
               res = 1; }
       else // no question
         res = 1;
         
       if(res == 0)
         _env_save_(env);
       _env_load_(cev);
   }
   _stk_zap_EXP_();
   _stk_poke_EXP_(tid);
   _stk_push_EXP_(_VOID_);
   _stk_poke_CNT_(SCH); }
   
/*------------------------------------------------------------------------*/
/*  THB (thread bind)                                                     */
/*     expr-stack: [... ... ... PAR ARG NBR] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... THB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THB(_NIL_TYPE_)
 { _EXP_TYPE_ arg, dct, exp, nam, nbr, par, set;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _mem_claim_();
   _stk_pop_EXP_(nbr);
   _stk_pop_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   if(ctr == siz)
     { _stk_zap_EXP_();
       _stk_zap_CNT_(); }
   else
     { _stk_peek_EXP_(par);
       nam = _ag_get_TAB_EXP_(par, ++ctr);
       exp = _ag_get_TAB_EXP_(arg, ctr);
       set = _ag_make_SET_();
       _ag_set_SET_INV_(set, nam);
       _ag_set_SET_EXP_(set, exp);
       nbr = _ag_succ_NBR_(nbr);
       _stk_push_EXP_(arg);
       _stk_push_EXP_(nbr);
       _stk_push_EXP_(set);
       _stk_push_CNT_(ZEX);
       _stk_push_CNT_(SET); }}
       
/*------------------------------------------------------------------------*/
/*  THE (thread evaluate arguments)                                       */
/*     expr-stack: [... ... ... ... NBR TAB] -> [... ... NBR TAB NBR EXP] */
/*     cont-stack: [... ... ... ... ... THE] -> [... ... THE RPL SWP EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... NBR TAB] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... THE] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THE(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, nbr, tha;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _mem_claim_();
   _stk_pop_EXP_(arg);
   _stk_peek_EXP_(nbr);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   if(ctr == siz)
     { _stk_zap_EXP_();
       _stk_zap_CNT_(); }
   else
     { exp = _ag_get_TAB_EXP_(arg, ++ctr);
       nbr = _ag_succ_NBR_(nbr);
       _stk_poke_EXP_(nbr);
       _stk_push_EXP_(arg);
       _stk_push_EXP_(nbr);
       _stk_push_EXP_(exp);
       _stk_push_CNT_(RPL);
       _stk_push_CNT_(SWI);
       _stk_push_CNT_(EXP); }}

/*------------------------------------------------------------------------*/
/*  THF (thread finished)                                                 */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... THF] -> [... ... ... ... THF EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THF(_NIL_TYPE_)
 { _EXP_TYPE_ exp, thr;
   _stk_claim_();
   thr = _ag_get_SCH_THR_(_SCH_CURRENT_);
   exp = _ag_get_THR_EXP_(thr);
   _stk_poke_EXP_(exp);
   _stk_push_CNT_(EXP); }

/*------------------------------------------------------------------------*/
/*  THQ (thread question)                                                 */
/*     expr-stack: [... ... ... ... ... THQ] -> [... ... ... ... THQ INV] */
/*     cont-stack: [... ... ... ... ... THQ] -> [... ... ... ... THq EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THQ(_NIL_TYPE_)
 { _EXP_TYPE_ inv, thq;
   _stk_claim_();
   _stk_peek_EXP_(thq);
   inv = _ag_get_THQ_INV_(thq);
   _stk_push_EXP_(inv);
   _stk_poke_CNT_(THq);
   _stk_push_CNT_(EXP); }

/*------------------------------------------------------------------------*/
/*  THq (thread question)                                                 */
/*     expr-stack: [... ... ... ... THQ TID] -> [... ... ... ... THQ TID] */
/*     cont-stack: [... ... ... ... ... THq] -> [... ... ... ... THq SCH] */
/*                                                                        */
/*     expr-stack: [... ... ... ... THQ TID] -> [... ... ... ... ... THQ] */
/*     cont-stack: [... ... ... ... ... THq] -> [... ... ... ... ... THQ] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THq(_NIL_TYPE_)
 { _EXP_TYPE_ tid;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _stk_peek_EXP_(tid);
   tag = _ag_get_TAG_(tid);
   if(tag != _TID_TAG_) // answering happens when calling the corresponding THA
     { _stk_zap_EXP_();
       _stk_poke_CNT_(THQ); }
   else // leave thread
     { _stk_push_EXP_(_VOID_);
       _stk_push_CNT_(SCH); }}

/*------------------------------------------------------------------------*/
/*  THR (thread)                                                          */
/*     expr-stack: [... ... ... ... ... THR] -> [... ... ... ... ... TID] */
/*     cont-stack: [... ... ... ... ... THR] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ THR(_NIL_TYPE_)
 { _EXP_TYPE_ cev, exp, env, nth, thr, tid;
   _mem_claim_();
   _stk_peek_EXP_(thr);
   _env_save_(cev);
   exp = _ag_get_THR_EXP_(thr);
   env = _env_initialise_(_DCT_);
   _env_load_(env);
   _stk_claim_();
   _stk_push_EXP_(exp);
   _stk_push_CNT_(THF);
   _stk_push_CNT_(EXP);
   _env_save_(env);
   _env_load_(cev);
   nth = _ag_make_THR_();
   _ag_set_THR_EXP_(nth, exp);
   _ag_set_THR_ENV_(nth, env);
   tid = _ag_make_TID_();
   _scheduler_add_(nth, tid);
   _stk_poke_EXP_(tid);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  ZEX (zap expression)                                                  */
/*     expr-stack: [... ... ... ... ... ***] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... ZEX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ ZEX(_NIL_TYPE_)
 { _stk_zap_EXP_();
   _stk_zap_CNT_(); }
  
/* public functions */

/*------------------------------------------------------------------------*/
/*  CAL                                                                   */
/*     expr-stack: [... ... ... ... FUN ARG] -> [... ... ... ... DCT EXP] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... RET EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... FUN ARG] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... ... EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... FUN ARG] -> [EXP DCT ARG TAB *1* EXP] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... ATV EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... FUN ARG] -> [EXP DCT ARG TAB *1* APL] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... ... ATA] */
/*                                                                        */
/*     expr-stack: [... ... ... ... FUN ARG] -> [EXP PAR ARG *1* DCT EXP] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... BND EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... FUN ARG] -> [EXP PAR ARG *1* DCT FUN] */
/*     cont-stack: [... ... ... ... ... CAL] -> [... ... ... ... ... BND] */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _eval_CAL_(_NIL_TYPE_)
 { _EXP_TYPE_ act, arg, dct, exp, frm, fun, nam, par, tab, xdc, xfu;
   _CNT_TYPE_ cnt;
   _TAG_TYPE_ tag, xtg;
   _UNS_TYPE_ siz, xsz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   tag = _ag_get_TAG_(arg);
   if (tag != _TAB_TAG_)  
     { _stk_zap_EXP_();
       _stk_peek_EXP_(fun);
       _error_msg_(_NAT_ERROR_, _ag_get_FUN_NAM_(fun)); }
   siz = _ag_get_TAB_SIZ_(arg);
   _mem_claim_SIZ_(siz);
   _stk_pop_EXP_(arg);
   if (siz == 0)
     { _stk_peek_EXP_(fun);
       par = _ag_get_FUN_ARG_(fun);
       tag = _ag_get_TAG_(par);
       switch (tag)
         { case _VAR_TAG_:
           case _APL_TAG_:
             dct = _ag_make_DCT_();
             par = _ag_get_FUN_ARG_(fun);
             nam = _ag_get_VAR_NAM_(par); 
             _ag_set_DCT_NAM_(dct, nam);
             _ag_set_DCT_VAL_(dct, _EMPTY_);
             xdc = _ag_get_FUN_DCT_(fun);
             _ag_set_DCT_DCT_(dct, xdc);
             break;
           case _TAB_TAG_:
             xsz = _ag_get_TAB_SIZ_(par);
             if (xsz == 0)
               dct = _ag_get_FUN_DCT_(fun);
             else
               _error_msg_(_NMA_ERROR_, _ag_get_FUN_NAM_(fun));
             break;
           default:
             _error_msg_(_IPM_ERROR_, _ag_get_FUN_NAM_(fun)); }
       exp = _ag_get_FUN_EXP_(fun);
       _stk_zap_CNT_();
       _stk_peek_CNT_(cnt);
       if (cnt != RET)
         { _stk_poke_EXP_(_DCT_);
           _stk_push_EXP_(exp); 
           _stk_push_CNT_(RET); }
       else
         _stk_poke_EXP_(exp);
       _stk_push_CNT_(EXP); 
       _DCT_ = dct; }
   else
     { dct = _ag_make_DCT_();
       _stk_peek_EXP_(fun);
       par = _ag_get_FUN_ARG_(fun);
       exp = _ag_get_FUN_EXP_(fun);
       xdc = _ag_get_FUN_DCT_(fun);
       tag = _ag_get_TAG_(par);
       switch (tag)
         { case _VAR_TAG_:
             nam = _ag_get_VAR_NAM_(par); 
             _ag_set_DCT_NAM_(dct, nam);
             _ag_set_DCT_DCT_(dct, xdc);
             _stk_poke_EXP_(exp);
             _stk_push_EXP_(dct);
             _stk_push_EXP_(arg);
             tab = _ag_make_TAB_(siz);
             act = _ag_get_TAB_EXP_(arg, 1);
             _stk_push_EXP_(tab);
             _stk_push_EXP_(_ONE_);
             _stk_push_EXP_(act);
             _stk_poke_CNT_(ATV);
             _stk_push_CNT_(EXP);
             break; 
           case _APL_TAG_:
             nam = _ag_get_APL_NAM_(par); 
             _ag_set_DCT_NAM_(dct, nam);
             _ag_set_DCT_DCT_(dct, xdc);
             _stk_poke_EXP_(exp);
             _stk_push_EXP_(dct);
             _stk_push_EXP_(arg);
             tab = _ag_make_TAB_(siz);
             _stk_push_EXP_(tab);
             _stk_push_EXP_(_ONE_);
             _stk_push_EXP_(par);
             _stk_poke_CNT_(ATA);
             break; 
           case _TAB_TAG_:
             xsz = _ag_get_TAB_SIZ_(par);
             if (siz != xsz)
               _error_msg_(_NMA_ERROR_, _ag_get_FUN_NAM_(fun));
             frm = _ag_get_TAB_EXP_(par, 1);
             xtg = _ag_get_TAG_(frm);
             switch (xtg)
              { case _VAR_TAG_:
                  act = _ag_get_TAB_EXP_(arg, 1);
                  _stk_poke_EXP_(exp);
                  _stk_push_EXP_(par);
                  _stk_push_EXP_(arg);
                  _stk_push_EXP_(_ONE_);
                  nam = _ag_get_VAR_NAM_(frm);
                  _ag_set_DCT_NAM_(dct, nam);
                  _ag_set_DCT_DCT_(dct, xdc);
                  _stk_push_EXP_(dct);
                  _stk_push_EXP_(act);
                  _stk_poke_CNT_(BND);
                  _stk_push_CNT_(EXP);
                  break;
                case _APL_TAG_:
                  xfu = _ag_make_FUN_();
                  par = _ag_get_FUN_ARG_(fun);
                  exp = _ag_get_FUN_EXP_(fun);
                  xdc = _ag_get_FUN_DCT_(fun);
                  act = _ag_get_TAB_EXP_(arg, 1);
                  frm = _ag_get_TAB_EXP_(par, 1);
                  _stk_poke_EXP_(exp);
                  _stk_push_EXP_(par);
                  _stk_push_EXP_(arg);
                  _stk_push_EXP_(_ONE_);
                  nam = _ag_get_APL_NAM_(frm);
                  arg = _ag_get_APL_ARG_(frm);
                  _ag_set_DCT_NAM_(dct, nam);
                  _ag_set_DCT_DCT_(dct, xdc);
                  _stk_push_EXP_(dct);
                  _ag_set_FUN_NAM_(xfu, nam);
                  _ag_set_FUN_ARG_(xfu, arg);
                  _ag_set_FUN_EXP_(xfu, act);
                  _ag_set_FUN_DCT_(xfu, _DCT_);
                  _stk_push_EXP_(xfu);
                  _stk_poke_CNT_(BND);
                   break; 
                default: 
                  _error_msg_(_IPM_ERROR_, _ag_get_FUN_NAM_(fun)); }
             break;
           default:
             _error_msg_(_IPM_ERROR_, _ag_get_FUN_NAM_(fun)); }}}
   
/*------------------------------------------------------------------------*/
/*  EXP                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... ***] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... EXP] -> [... ... ... ... *** SCH] */
/*------------------------------------------------------------------------*/ 
_NIL_TYPE_ _eval_EXP_(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _CNT_TYPE_ cnt;
   _stk_claim_();
   _stk_peek_EXP_(exp);
   cnt = CNT_tab[_ag_get_TAG_(exp)];
   if(eval_counter-- == 0)
     { _stk_poke_CNT_(cnt);
       _stk_push_EXP_(_VOID_);
       _stk_push_CNT_(SCH);
       eval_counter = max; }
   else
     { _stk_poke_CNT_(cnt); }}
   
/*------------------------------------------------------------------------*/
/*  Main Expression (initializes everything with new input)               */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... MEX] -> [... ... ... ... EXP SCH] */
/*------------------------------------------------------------------------*/ 
_NIL_TYPE_ _eval_main_EXP_(_NIL_TYPE_)
 { _EXP_TYPE_ dct, env, sch, thr, tid;
   eval_counter = max;
   _scheduler_initialize_();
   _stk_poke_CNT_(EXP);
   _mem_claim_();
   thr = _ag_make_THR_();
   env = _ag_make_ENV_();
   tid = _ag_make_TID_();
   dct = _ag_make_DCT_();
   _ag_set_DCT_NAM_(dct, _env_make_NAM_("main"));
   _ag_set_DCT_VAL_(dct, tid);
   _ag_set_DCT_DCT_(dct, _DCT_);
   _DCT_ = dct;
   sch = _scheduler_add_(thr, tid);
   _env_save_(env);
   _ag_set_THR_ENV_(thr, env); }
