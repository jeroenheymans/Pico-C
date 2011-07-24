/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*              Reading              */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/*EXPRESSION                                                              */
/*   <exp> ::= <inv>                                                      */
/*   <exp> ::= <inv> ':'  <exp>                      => (DEF <inv> <exp>) */
/*   <exp> ::= <inv> ':=' <exp>                      => (SET <inv> <exp>) */
/*   <exp> ::= <inv> ':?:' <exp>                     => (PRA <inv> <exp>) */
/*   <exp> ::= <inv> ':!:' <exp>                     => (PRG <inv> <exp>) */
/*INVOCATION                                                              */
/*   <inv> ::= <cmp>                                                      */
/*   <inv> ::= <cmp> #rop# <inv>         => (APL #rop# (TBL <cmp> <inv>)) */
/*COMPARAND                                                               */
/*   <cmp> ::= <trm>                                                      */
/*   <cmp> ::= <trm> #aop# <cmp>         => (APL #aop# (TBL <trm> <cmp>)) */
/*TERM                                                                    */
/*   <trm> ::= <fct>                                                      */
/*   <trm> ::= <fct> #mop# <trm>         => (APL #mop# (TBL <fct> <trm>)) */
/*FACTOR                                                                  */
/*   <fct> ::= <ref>                                                      */
/*   <fct> ::= <ref> #xop# <fct>         => (APL #xop# (TBL <ref> <fct>)) */
/*REFERENCE                                                               */
/*   <ref> ::= <sub>                                                      */
/*   <ref> ::= <tbl>                                                      */
/*   <ref> ::= <bgn>                                                      */
/*   <ref> ::= <unr>                                                      */
/*   <ref> ::= <inv>                                                      */
/*   <ref> ::= <tab>                                                      */
/*   <ref> ::= <var>                                                      */
/*   <ref> ::= <nbr>                                                      */
/*   <ref> ::= <sym>                                                      */
/*   <ref> ::= <pro>                                                      */
/*   <ref> ::= <spr>                                                      */
/*PROCESS                                                                 */
/*   <pro> ::= '(:' <exp> ':)'                                            */
/*SEQUENCE PROCESS                                                        */
/*   <spr> ::= '{:' <smc> ':}'                                            */
/*SUBEXPRESSION                                                           */
/*   <sub> ::= '(' <exp> ')'                                              */
/*TABLE                                                                   */
/*   <tbl> ::= '[' ']'                             => (APL #table# (TAB)) */
/*   <tbl> ::= '[' <com> ']'                 => (APL #table# (TAB <com>)) */
/*BEGIN                                                                   */
/*   <bgn> ::= '{' <smc> '}'                 => (APL #begin# (TAB <smc>)) */
/*UNARY                                                                   */
/*   <unr> ::= <opr> <ref>                     => (APL <opr> (TAB <ref>)) */
/*APPLICATION                                                             */
/*   <apl> ::= <idf> '(' ')'                         => (APL <idf> (TAB)) */
/*   <apl> ::= <idf> '(' <com> ')'             => (APL <idf> (TAB <com>)) */
/*   <apl> ::= <idf> '@' <ref>                       => (APL <idf> <ref>) */
/*TABULATION                                                              */
/*   <tab> ::= <idf> '[' <idx> ']'                   => (TBL <idf> <idx>) */
/*COMMALIST                                                               */
/*   <com>  ::= <exp>                                            => <exp> */
/*   <com>  ::= <exp> ',' <com>                            => <exp> <com> */
/*SEMICOLONLIST                                                           */
/*   <smc>  ::= <exp>                                            => <exp> */
/*   <smc>  ::= <exp> ';' <smc>                            => <exp> <smc> */
/*INDEX                                                                   */
/*   <idx>  ::= <exp>                                                     */
/*OPERATOR                                                                */
/*   <opr> ::= #rop#                                                      */
/*   <opr> ::= #aop#                                                      */
/*   <opr> ::= #mop#                                                      */
/*IDENTIFIER                                                              */
/*   <idf> ::= #nam#                                                      */
/*VARIABLE                                                                */
/*   <var> ::= <idf>                                       => (VAR <idf>) */
/*   <var> ::= <opr>                                       => (VAR <opr>) */
/*                                                                        */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoEnv.h"
#include "PicoNat.h"
#include "PicoSca.h"
#include "PicoRea.h"

/* private macros */

#define READ_TOKEN()\
  current_token = _scan_()
 
/* private prototypes */

static _NIL_TYPE_ APL(_NIL_TYPE_);
static _NIL_TYPE_ BIN(_NIL_TYPE_);
static _NIL_TYPE_ CMP(_NIL_TYPE_);
static _NIL_TYPE_ CMp(_NIL_TYPE_);
static _NIL_TYPE_ CEX(_NIL_TYPE_);
static _NIL_TYPE_ CEx(_NIL_TYPE_);
static _NIL_TYPE_ COM(_NIL_TYPE_);
static _NIL_TYPE_ DEF(_NIL_TYPE_);
static _NIL_TYPE_ EXP(_NIL_TYPE_);
static _NIL_TYPE_ EXp(_NIL_TYPE_);
static _NIL_TYPE_ EXT(_NIL_TYPE_);
static _NIL_TYPE_ FCT(_NIL_TYPE_);
static _NIL_TYPE_ FCt(_NIL_TYPE_);
static _NIL_TYPE_ IDX(_NIL_TYPE_);
static _NIL_TYPE_ INV(_NIL_TYPE_);
static _NIL_TYPE_ INv(_NIL_TYPE_);
static _NIL_TYPE_ NRY(_NIL_TYPE_);
static _NIL_TYPE_ NRy(_NIL_TYPE_);
static _NIL_TYPE_ PRA(_NIL_TYPE_); /* added */
static _NIL_TYPE_ PRG(_NIL_TYPE_); /* added */
static _NIL_TYPE_ PRO(_NIL_TYPE_); /* added */
static _NIL_TYPE_ REF(_NIL_TYPE_);
static _NIL_TYPE_ RPR(_NIL_TYPE_);
static _NIL_TYPE_ SET(_NIL_TYPE_);
static _NIL_TYPE_ SMC(_NIL_TYPE_);
static _NIL_TYPE_ SPR(_NIL_TYPE_);
static _NIL_TYPE_ TBL(_NIL_TYPE_);
static _NIL_TYPE_ TRM(_NIL_TYPE_);
static _NIL_TYPE_ TRm(_NIL_TYPE_);
static _NIL_TYPE_ UNR(_NIL_TYPE_);
static _NIL_TYPE_ VAR(_NIL_TYPE_);

/* private variables */

static _TKN_TYPE_ current_token;

/* private functions */

static _EXP_TYPE_ make_nam(_NIL_TYPE_)
 { _EXP_TYPE_ exp;
   _STR_TYPE_ str;
   str = _scan_string_();
   _mem_claim_STR_(str);
   exp = _env_make_NAM_(str);
   READ_TOKEN();
   return exp; }
   
/*------------------------------------------------------------------------*/
/*  APL                                                                   */
/*     expr-stack: [... ... ... ... NAM ARG] -> [... ... ... ... ... APL] */
/*     cont-stack: [... ... ... ... CNT APL] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ APL(_NIL_TYPE_)
 { _EXP_TYPE_ apl, arg, nam;
   _mem_claim_();
   apl = _ag_make_APL_();    
   _stk_pop_EXP_(arg);
   _stk_peek_EXP_(nam);
   _ag_set_APL_NAM_(apl, nam);      
   _ag_set_APL_ARG_(apl, arg);      
   _stk_poke_EXP_(apl);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  BIN                                                                   */
/*     expr-stack: [... ... ... NAM EXP EXP] -> [... ... ... ... NAM TAB] */
/*     cont-stack: [... ... ... ... CNT BIN] -> [... ... ... ... CNT APL] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ BIN(_NIL_TYPE_)
 { _EXP_TYPE_ exp_1, exp_2, tab;
   _mem_claim_();
   tab = _ag_make_TAB_(2);    
   _stk_pop_EXP_(exp_2);
   _stk_peek_EXP_(exp_1);
   _ag_set_TAB_EXP_(tab, 1, exp_1);
   _ag_set_TAB_EXP_(tab, 2, exp_2);
   _stk_poke_EXP_(tab);
   _stk_poke_CNT_(APL); }

/*------------------------------------------------------------------------*/
/*  CMP                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT CMP] -> [... ... ... CNT CMp TRM] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ CMP(_NIL_TYPE_)
 { _stk_claim_();
   _stk_poke_CNT_(CMp);
   _stk_push_CNT_(TRM); }
 
/*------------------------------------------------------------------------*/
/*  CMp                                                                   */
/*     expr-stack: [... ... ... ... ... TRM] -> [... ... ... ... NAM TRM] */
/*     cont-stack: [... ... ... ... CNT CMp] -> [... ... CNT CMp BIN TRM] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... TRM] -> [... ... ... ... ... TRM] */
/*     cont-stack: [... ... ... ... CNT CMp] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ CMp(_NIL_TYPE_)
 { _EXP_TYPE_ nam, trm;
   _stk_claim_();
   if (current_token == _AOP_TOKEN_)
     { nam = make_nam();
       _stk_peek_EXP_(trm);
       _stk_poke_EXP_(nam);
       _stk_push_EXP_(trm);
       _stk_push_CNT_(BIN);
       _stk_push_CNT_(TRM); }
   else
     _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  COM                                                                   */
/*     expr-stack: [NAM EXP ... EXP NBR EXP] -> [NAM EXP ... EXP EXP NBR] */
/*     cont-stack: [... ... ... ... CNT COM] -> [... ... ... CNT COM EXP] */
/*                                                                        */
/*     expr-stack: [NAM EXP ... EXP NBR EXP] -> [... ... ... ... NAM TAB] */
/*     cont-stack: [... ... ... ... CNT COM] -> [... ... ... ... CNT APL] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ COM(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr, tab;
   _UNS_TYPE_ ctr;
   _stk_claim_();
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(nbr);
   _stk_poke_EXP_(exp);
   switch (current_token)
     { case _RBR_TOKEN_: 
         READ_TOKEN();
         ctr = _ag_get_NBU_(nbr);
         _mem_claim_SIZ_(ctr);
         tab = _ag_make_TAB_(ctr);    
         do
           { _stk_pop_EXP_(exp);
             _ag_set_TAB_EXP_(tab, ctr, exp); } 
         while (--ctr);
         _stk_push_EXP_(tab);
         _stk_poke_CNT_(APL);
         break;
       case _COM_TOKEN_:
         READ_TOKEN();
         nbr = _ag_succ_NBR_(nbr);
         _stk_push_EXP_(nbr);
         _stk_push_CNT_(EXP); 
         break; 
       default:
         _scan_error_(_RBR_ERROR_); }}
   
/*------------------------------------------------------------------------*/
/*  DEF                                                                   */
/*     expr-stack: [... ... ... ... INV EXP] -> [... ... ... ... ... DEF] */
/*     cont-stack: [... ... ... ... CNT DEF] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ DEF(_NIL_TYPE_)
 { _EXP_TYPE_ def, exp, inv;
   _mem_claim_();
   def = _ag_make_DEF_();    
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(inv);
   _ag_set_DEF_INV_(def, inv);      
   _ag_set_DEF_EXP_(def, exp);      
   _stk_poke_EXP_(def);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  EXP                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT EXP] -> [... ... ... CNT EXp INV] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ EXP(_NIL_TYPE_)
 { _stk_claim_();
   _stk_poke_CNT_(EXp);
   _stk_push_CNT_(INV); }

/*------------------------------------------------------------------------*/
/*  EXp                                                                   */
/*     expr-stack: [... ... ... ... ... INV] -> [... ... ... ... ... INV] */
/*     cont-stack: [... ... ... ... CNT EXP] -> [... ... ... CNT DEF EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... INV] -> [... ... ... ... ... INV] */
/*     cont-stack: [... ... ... ... CNT EXP] -> [... ... ... CNT INI EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... INV] -> [... ... ... ... ... INV] */
/*     cont-stack: [... ... ... ... CNT EXP] -> [... ... ... CNT SET EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... INV] -> [... ... ... ... ... INV] */
/*     cont-stack: [... ... ... ... CNT EXP] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ EXp(_NIL_TYPE_)
 { _stk_claim_();
   switch (current_token)
     { case _COL_TOKEN_:
         READ_TOKEN();
         _stk_poke_CNT_(DEF);
         _stk_push_CNT_(EXP);
         break;
       case _CEQ_TOKEN_:
         READ_TOKEN();
         _stk_poke_CNT_(SET);
         _stk_push_CNT_(EXP);
         break;
       case _PRA_TOKEN_: /* added */
		READ_TOKEN();
		_stk_poke_CNT_(PRA);
		_stk_push_CNT_(EXP);
		break;
	  case _PRG_TOKEN_: /* added */
		READ_TOKEN();
		_stk_poke_CNT_(PRG);
		_stk_push_CNT_(EXP);
		break;
       default:
         _stk_zap_CNT_(); }}

/*------------------------------------------------------------------------*/
/*  EXT                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... CNT EXT] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ EXT(_NIL_TYPE_)
 { if (current_token != _END_TOKEN_)
     _scan_error_(_EXT_ERROR_); 
   _stk_zap_CNT_(); }
     
/*------------------------------------------------------------------------*/
/*  FCT                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT FCT] -> [... ... ... CNT FC1 REF] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ FCT(_NIL_TYPE_)
 { _stk_claim_();
   _stk_poke_CNT_(FCt);
   _stk_push_CNT_(REF); }
 
/*------------------------------------------------------------------------*/
/*  FCt                                                                   */
/*     expr-stack: [... ... ... ... ... REF] -> [... ... ... ... NAM REF] */
/*     cont-stack: [... ... ... ... CNT FCt] -> [... ... CNT FCt BIN REF] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... REF] -> [... ... ... ... ... REF] */
/*     cont-stack: [... ... ... ... CNT FCt] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ FCt(_NIL_TYPE_)
 { _EXP_TYPE_ nam, ref;
   _stk_claim_();
   if (current_token == _XOP_TOKEN_)
     { nam = make_nam();
       _stk_peek_EXP_(ref);
       _stk_poke_EXP_(nam);
       _stk_push_EXP_(ref);
       _stk_push_CNT_(BIN);
       _stk_push_CNT_(REF); }
   else
     _stk_zap_CNT_(); }
 
/*------------------------------------------------------------------------*/
/*  IDX                                                                   */
/*     expr-stack: [... ... ... ... NAM EXP] -> [... ... ... ... NAM EXP] */
/*     cont-stack: [... ... ... ... CNT IDX] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ IDX(_NIL_TYPE_)
 { if (current_token == _RBR_TOKEN_)
     { READ_TOKEN();
       _stk_zap_CNT_(); }
   else
     _scan_error_(_RBR_ERROR_); }
 
/*------------------------------------------------------------------------*/
/*  INV                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT INV] -> [... ... ... CNT IN1 CMP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ INV(_NIL_TYPE_)
 { _stk_claim_();
   _stk_poke_CNT_(INv);
   _stk_push_CNT_(CMP); }
 
/*------------------------------------------------------------------------*/
/*  INv                                                                   */
/*     expr-stack: [... ... ... ... ... CMP] -> [... ... ... ... NAM CMP] */
/*     cont-stack: [... ... ... ... CNT INv] -> [... ... CNT INv BIN CMP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... CMP] -> [... ... ... ... ... CMP] */
/*     cont-stack: [... ... ... ... CNT INv] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ INv(_NIL_TYPE_)
 { _EXP_TYPE_ cmp, nam;
   _stk_claim_();
   if (current_token == _ROP_TOKEN_)
     { nam = make_nam();
       _stk_peek_EXP_(cmp);
       _stk_poke_EXP_(nam);
       _stk_push_EXP_(cmp);
       _stk_push_CNT_(BIN);
       _stk_push_CNT_(CMP); }
   else
     _stk_zap_CNT_(); }
     
/*------------------------------------------------------------------------*/
/*  NRY                                                                   */
/*     expr-stack: [... ... ... ... ... NAM] -> [... ... ... ... NAM *E*] */
/*     cont-stack: [... ... ... ... CNT NRY] -> [... ... ... ... ... CNT] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... NAM] -> [... ... ... ... NAM *1*] */
/*     cont-stack: [... ... ... ... CNT NRY] -> [... ... ... CNT NR1 EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NRY(_NIL_TYPE_)
 { _stk_claim_();
   if (current_token == _RPR_TOKEN_)
     { READ_TOKEN();
       _stk_push_EXP_(_EMPTY_);
       _stk_zap_CNT_(); }
   else
     { _stk_push_EXP_(_ONE_);
       _stk_poke_CNT_(NRy);
       _stk_push_CNT_(EXP); }}
     
/*------------------------------------------------------------------------*/
/*  NRy                                                                   */
/*     expr-stack: [NAM EXP ... EXP NBR EXP] -> [... ... ... ... NAM TAB] */
/*     cont-stack: [... ... ... ... CNT NRy] -> [... ... ... ... ... CNT] */
/*                                                                        */
/*     expr-stack: [NAM EXP ... EXP NBR EXP] -> [NAM EXP ... EXP EXP NBR] */
/*     cont-stack: [... ... ... ... CNT NRy] -> [... ... ... CNT NRy EXP] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ NRy(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr, tab;
   _UNS_TYPE_ idx;
   _stk_claim_();
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(nbr);
   _stk_poke_EXP_(exp);
   switch (current_token)
     { case _RPR_TOKEN_:
         READ_TOKEN();
         idx = _ag_get_NBU_(nbr);
        _mem_claim_SIZ_(idx);
         tab = _ag_make_TAB_(idx);    
         do
           { _stk_pop_EXP_(exp);
             _ag_set_TAB_EXP_(tab, idx, exp); } 
         while (--idx);
         _stk_push_EXP_(tab);
         _stk_zap_CNT_();
         break;
       case _COM_TOKEN_:
         READ_TOKEN();
         nbr = _ag_succ_NBR_(nbr);
         _stk_push_EXP_(nbr);
         _stk_push_CNT_(EXP); 
         break; 
       default:
         _scan_error_(_RPR_ERROR_); }}
         
/*------------------------------------------------------------------------*/
/*  PRA                                                                   */
/*     expr-stack: [... ... ... ... INV EXP] -> [... ... ... ... ... PRA] */
/*     cont-stack: [... ... ... ... CNT PRO] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ PRA(_NIL_TYPE_)
 { _EXP_TYPE_ pra, apl, nam;
   _mem_claim_();  
   _stk_pop_EXP_(apl);
   _stk_peek_EXP_(nam);
   pra = _ag_make_PRA_();  
   _ag_set_PRA_NAM_(pra, nam);      
   _ag_set_PRA_APL_(pra, apl);      
   _stk_poke_EXP_(pra);
   _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  PRG                                                                   */
/*     expr-stack: [... ... ... ... INV EXP] -> [... ... ... ... ... PRG] */
/*     cont-stack: [... ... ... ... CNT PRG] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ PRG(_NIL_TYPE_)
 { _EXP_TYPE_ prg, apl, nam;
   _mem_claim_();
   _stk_pop_EXP_(apl);
   _stk_peek_EXP_(nam);
   prg = _ag_make_PRG_();   
   _ag_set_PRG_NAM_(prg, nam);      
   _ag_set_PRG_APL_(prg, apl);      
   _stk_poke_EXP_(prg);
   _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  PRO                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... PRO] */
/*     cont-stack: [... ... ... ... CNT PRO] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ PRO(_NIL_TYPE_)
 { _EXP_TYPE_ pro, exp, tab, ctr;
   _UNS_TYPE_ siz = 1;
   _mem_claim_();
   _stk_pop_EXP_(exp);
   _mem_claim_SIZ_(siz);
   pro = _ag_make_PRO_();
   ctr = _ag_make_NBR_(1);
   tab = _ag_make_TAB_(siz);
   _ag_set_TAB_EXP_(tab, siz, exp);
   _ag_set_PRO_EXP_(pro, tab);
   _stk_push_EXP_(pro);
   if (current_token == _PRE_TOKEN_)
     { READ_TOKEN();
       _stk_zap_CNT_(); }
   else
     _scan_error_(_PRO_ERROR_); }
   
/*------------------------------------------------------------------------*/
/*  REF                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... CNT RPR EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... *T* *E*] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... CNT APL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... *T* *1*] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... CNT RBR EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... *B* *1*] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... CNT RBC EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... CNT APL NRY] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... CNT APL REF] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... CNT TBL IDX EXP] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... CNT VAR] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... CNT MSG] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NAM] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... CNT APL UNR REF] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... NBR] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... ... CNT] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... FRC] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... ... CNT] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... STR] */
/*     cont-stack: [... ... ... ... CNT REF] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ REF(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nam;
   _SGN_TYPE_ nbr;
   _FLO_TYPE_ frc;
   _STR_TYPE_ str;
   _stk_claim_();
   _mem_claim_();
   switch (current_token)
     { case _PRB_TOKEN_:
         READ_TOKEN();
         _stk_poke_CNT_(PRO);
         _stk_push_CNT_(EXP);
         break;
       case _SPB_TOKEN_:
         READ_TOKEN();
         _stk_push_EXP_(_BEGIN_);
         _stk_push_EXP_(_ONE_);
         _stk_poke_CNT_(SPR);
         _stk_push_CNT_(EXP);
         break;
       case _LPR_TOKEN_:
         READ_TOKEN();
         _stk_poke_CNT_(RPR);
         _stk_push_CNT_(EXP);
         break; 
       case _LBR_TOKEN_:
         READ_TOKEN();
         _stk_push_EXP_(_TAB_);
         if (current_token == _RBR_TOKEN_)
           { READ_TOKEN();
             _stk_push_EXP_(_EMPTY_);
             _stk_poke_CNT_(APL); }
         else
           { _stk_push_EXP_(_ONE_);
             _stk_poke_CNT_(COM);
             _stk_push_CNT_(EXP); }
         break; 
       case _LBC_TOKEN_:
         READ_TOKEN();
         _stk_push_EXP_(_BEGIN_);
         _stk_push_EXP_(_ONE_);
         _stk_poke_CNT_(SMC);
         _stk_push_CNT_(EXP);
         break; 
       case _NAM_TOKEN_:
         nam = make_nam();
         _stk_push_EXP_(nam);
         switch (current_token)
           { case _LPR_TOKEN_:
               READ_TOKEN();
               _stk_poke_CNT_(APL);
               _stk_push_CNT_(NRY);
               break; 
             case _CAT_TOKEN_:
               READ_TOKEN();
               _stk_poke_CNT_(APL);
               _stk_push_CNT_(REF);
               break; 
             case _LBR_TOKEN_:
               READ_TOKEN();
               _stk_poke_CNT_(TBL);
               _stk_push_CNT_(IDX);
               _stk_push_CNT_(EXP);
               break; 
             default:
               _stk_poke_CNT_(VAR); }
         break;
       case _ROP_TOKEN_:
       case _AOP_TOKEN_:
       case _MOP_TOKEN_:
       case _XOP_TOKEN_:
         nam = make_nam();
         _stk_push_EXP_(nam);
         switch (current_token)
           { case _LPR_TOKEN_:
               READ_TOKEN();
               _stk_poke_CNT_(APL);
               _stk_push_CNT_(NRY);
               break; 
             case _CAT_TOKEN_:
               READ_TOKEN();
               _stk_poke_CNT_(APL);
               _stk_push_CNT_(REF);
               break; 
             case _NBR_TOKEN_:
             case _FRC_TOKEN_:
             case _TXT_TOKEN_:
             case _NAM_TOKEN_:
               _stk_poke_CNT_(APL);
               _stk_push_CNT_(UNR);
               _stk_push_CNT_(REF);
               break; 
             default:
               _stk_poke_CNT_(VAR); }
         break; 
       case _NBR_TOKEN_:
         { nbr = _scan_number_();
           exp = _ag_make_NBR_(nbr);     
           READ_TOKEN();
           _stk_push_EXP_(exp);
           _stk_zap_CNT_();
           break; }
       case _FRC_TOKEN_:
         { frc = _scan_fraction_();
           exp = _ag_make_FRC_(&frc);    
           READ_TOKEN();
           _stk_push_EXP_(exp);
           _stk_zap_CNT_();
           break; }
       case _TXT_TOKEN_:
         { str = _scan_string_();
           _mem_claim_STR_(str);
           exp = _env_make_NAM_(str);    
           READ_TOKEN();
           _stk_push_EXP_(exp);
           _stk_zap_CNT_();
           break; }
       default:
         _scan_error_(_REF_ERROR_); }}
 
/*------------------------------------------------------------------------*/
/*  RPR                                                                   */
/*     expr-stack: [... ... ... ... ... EXP] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... CNT RPR] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ RPR(_NIL_TYPE_)
 { if (current_token == _RPR_TOKEN_)
     { READ_TOKEN();
       _stk_zap_CNT_(); }
   else
     _scan_error_(_RPR_ERROR_); }
   
/*------------------------------------------------------------------------*/
/*  SET                                                                   */
/*     expr-stack: [... ... ... ... INV EXP] -> [... ... ... ... ... SET] */
/*     cont-stack: [... ... ... ... CNT SET] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SET(_NIL_TYPE_)
 { _EXP_TYPE_ exp, inv, set;
   _mem_claim_();
   set = _ag_make_SET_();    
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(inv);
   _ag_set_SET_INV_(set, inv);      
   _ag_set_SET_EXP_(set, exp);      
   _stk_poke_EXP_(set);
   _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  SMC                                                                   */
/*     expr-stack: [... NAM ... EXP NBR EXP] -> [... NAM ... EXP EXP NBR] */
/*     cont-stack: [... ... ... ... CNT SMC] -> [... ... ... CNT SMC EXP] */
/*                                                                        */
/*     expr-stack: [... NAM ... EXP NBR EXP] -> [... ... ... ... NAM TAB] */
/*     cont-stack: [... ... ... ... CNT SMC] -> [... ... ... ... CNT APL] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SMC(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr, tab;
   _UNS_TYPE_ ctr;
   _stk_claim_();
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(nbr);
   _stk_poke_EXP_(exp);
   switch (current_token)
     { case _RBC_TOKEN_: 
         READ_TOKEN();
         ctr = _ag_get_NBU_(nbr);
         _mem_claim_SIZ_(ctr);
         tab = _ag_make_TAB_(ctr);    
         do
           { _stk_pop_EXP_(exp);
             _ag_set_TAB_EXP_(tab, ctr, exp); } 
         while (--ctr);
         _stk_push_EXP_(tab);
         _stk_poke_CNT_(APL);
         break;
       case _SMC_TOKEN_:
         READ_TOKEN();
         _stk_push_EXP_(_ag_succ_NBR_(nbr));
         _stk_push_CNT_(EXP); 
         break; 
       default:
         _scan_error_(_RBC_ERROR_); }}

/*------------------------------------------------------------------------*/
/*  SPR                                                                   */
/*     expr-stack: [... ... ... ... INV EXP] -> [... ... ... ... ... PRG] */
/*     cont-stack: [... ... ... ... CNT PRG] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ SPR(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr, tab, pro;
   _UNS_TYPE_ ctr;
   _stk_claim_();
   _stk_pop_EXP_(exp);
   _stk_peek_EXP_(nbr);
   _stk_poke_EXP_(exp);
   switch (current_token)
     { case _SPE_TOKEN_: 
         READ_TOKEN();
         ctr = _ag_get_NBU_(nbr);
         _mem_claim_SIZ_(ctr);
         tab = _ag_make_TAB_(ctr);    
         do
           { _stk_pop_EXP_(exp);
             _ag_set_TAB_EXP_(tab, ctr, exp); } 
         while (--ctr);
   		 pro = _ag_make_PRO_(); 
   		 _ag_set_PRO_EXP_(pro, tab);
   		 _stk_poke_EXP_(pro);
   		 _stk_zap_CNT_();
         break;
       case _SMC_TOKEN_:
         READ_TOKEN();
         _stk_push_EXP_(_ag_succ_NBR_(nbr));
         _stk_push_CNT_(EXP);
         break; 
       default:
         _scan_error_(_SPR_ERROR_); }}

/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... NAM EXP] -> [... ... ... ... ... TBL] */
/*     cont-stack: [... ... ... ... CNT TBL] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TBL(_NIL_TYPE_)
 { _EXP_TYPE_ idx, nam, tbl;
   _mem_claim_();
   tbl = _ag_make_TBL_();    
   _stk_pop_EXP_(idx);
   _stk_peek_EXP_(nam);
   _ag_set_TBL_NAM_(tbl, nam);      
   _ag_set_TBL_IDX_(tbl, idx);      
   _stk_poke_EXP_(tbl);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  TRM                                                                   */
/*     expr-stack: [... ... ... ... ... ...] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... CNT TRM] -> [... ... ... CNT TRm FCT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TRM(_NIL_TYPE_)
 { _stk_claim_();
   _stk_poke_CNT_(TRm);
   _stk_push_CNT_(FCT); }
 
/*------------------------------------------------------------------------*/
/*  TRm                                                                   */
/*     expr-stack: [... ... ... ... ... FCT] -> [... ... ... ... NAM FCT] */
/*     cont-stack: [... ... ... ... CNT TRm] -> [... ... CNT TRm BIN FCT] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... FCT] -> [... ... ... ... ... FCT] */
/*     cont-stack: [... ... ... ... CNT TRm] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ TRm(_NIL_TYPE_)
 { _EXP_TYPE_ fct, nam;
   _stk_claim_();
   if (current_token == _MOP_TOKEN_)
     { nam = make_nam();
       _stk_peek_EXP_(fct);
       _stk_poke_EXP_(nam);
       _stk_push_EXP_(fct);
       _stk_push_CNT_(BIN);
       _stk_push_CNT_(FCT); }
   else
     _stk_zap_CNT_(); }
 
/*------------------------------------------------------------------------*/
/*  UNR                                                                   */
/*     expr-stack: [... ... ... ... NAM EXP] -> [... ... ... ... NAM TAB] */
/*     cont-stack: [... ... ... ... CNT UNR] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ UNR(_NIL_TYPE_)
 { _EXP_TYPE_ exp, tab;
   _mem_claim_();
   tab = _ag_make_TAB_(1);    
   _stk_peek_EXP_(exp);
   _ag_set_TAB_EXP_(tab, 1, exp);
   _stk_poke_EXP_(tab);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  VAR                                                                   */
/*     expr-stack: [... ... ... ... ... NAM] -> [... ... ... ... ... VAR] */
/*     cont-stack: [... ... ... ... CNT VAR] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
static _NIL_TYPE_ VAR(_NIL_TYPE_)
 { _EXP_TYPE_ nam, var;
   _mem_claim_();
   var = _ag_make_VAR_();    
   _stk_peek_EXP_(nam);
   _ag_set_VAR_NAM_(var, nam);      
   _stk_poke_EXP_(var);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/* public functions */

/*------------------------------------------------------------------------*/
/*  REA                                                                   */
/*     expr-stack: [... ... ... ... STR BLN] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... CNT REA] -> [... ... ... ... ... CNT] */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _read_EXP_(_NIL_TYPE_)
 {  _EXP_TYPE_ bln, str;
   _stk_pop_EXP_(bln);
   _stk_pop_EXP_(str);
   _scan_init_(_ag_get_TXT_(str), _ag_is_VOI_(bln));
   _stk_claim_();
   current_token = _scan_();
   _stk_poke_CNT_(EXT);
   _stk_push_CNT_(EXP); }
