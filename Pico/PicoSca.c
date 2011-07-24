/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*              Scanning             */
/*-----------------------------------*/

/*-----------------------------------*/
/*  integer            =>  <integer> */
/*  float              =>  <float>   */
/*  text               =>  <string>  */
/*  name               =>  <string>  */
/*  relop              =>  <string>  */
/*  mulop              =>  <string>  */
/*  addop              =>  <string>  */
/*  left-parenthesis   =>  <null>    */
/*  right-parenthesis  =>  <null>    */
/*  left-bracket       =>  <null>    */
/*  right-bracket      =>  <null>    */
/*  left-brace         =>  <null>    */
/*  right-brace        =>  <null>    */
/*  colon              =>  <null>    */
/*  colon-equal        =>  <null>    */
/*  semicolon          =>  <null>    */
/*  comma              =>  <null>    */
/*  commercial-at      =>  <null>    */
/*  end-of-entry       =>  <null>    */
/*-----------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoSca.h"

/* private macros */

#define SCAN_CHECK(allowed)\
  (scan_ch && ((allowed >> scan_char_tab[scan_ch]) & 1))

#define SCAN_UNCHECK(allowed)\
  (scan_ch && !((allowed >> scan_char_tab[scan_ch]) & 1))

#define SCAN_NEXT_CH()\
  (scan_ch = scan_text[scan_stop]) ? scan_stop++ : 0

/* private types */

typedef enum scan_fun_index { Aop =  0,
                              Apo =  1,
                              Bkq =  2,
                              Cat =  3,
                              Col =  4,
                              Com =  5,
                              Dgt =  6,
                              Eol =  7,
                              Eql =  8,
                              Exp =  9,
                              Ill = 10,
                              Lbc = 11,
                              Lbr = 12,
                              Lpr = 13,
                              Ltr = 14,
                              Mns = 15,
                              Mop = 16,
                              Per = 17,
                              Pls = 18,
                              Quo = 19,
                              Rbc = 20,
                              Rbr = 21,
                              Rop = 22,
                              Rpr = 23,
                              Smc = 24,
                              Wsp = 25,
                              Sir = 26, /* added */
                              Exm = 27, /* added */
                              Qum = 28 } scan_fun_index; /* added */

typedef _TKN_TYPE_ scan_fun(_NIL_TYPE_);

/* private prototypes */

static _TKN_TYPE_ scan_Aop(_NIL_TYPE_);
static _TKN_TYPE_ scan_Apo(_NIL_TYPE_);
static _TKN_TYPE_ scan_Bkq(_NIL_TYPE_);
static _TKN_TYPE_ scan_Cat(_NIL_TYPE_);
static _TKN_TYPE_ scan_Col(_NIL_TYPE_);
static _TKN_TYPE_ scan_Com(_NIL_TYPE_);
static _TKN_TYPE_ scan_Dgt(_NIL_TYPE_);
static _TKN_TYPE_ scan_Ill(_NIL_TYPE_);
static _TKN_TYPE_ scan_Ltr(_NIL_TYPE_);
static _TKN_TYPE_ scan_Lbc(_NIL_TYPE_);
static _TKN_TYPE_ scan_Lbr(_NIL_TYPE_);
static _TKN_TYPE_ scan_Lpr(_NIL_TYPE_);
static _TKN_TYPE_ scan_Mop(_NIL_TYPE_);
static _TKN_TYPE_ scan_Quo(_NIL_TYPE_);
static _TKN_TYPE_ scan_Rbc(_NIL_TYPE_);
static _TKN_TYPE_ scan_Rbr(_NIL_TYPE_);
static _TKN_TYPE_ scan_Rop(_NIL_TYPE_);
static _TKN_TYPE_ scan_Rpr(_NIL_TYPE_);
static _TKN_TYPE_ scan_Smc(_NIL_TYPE_);
static _TKN_TYPE_ scan_Wsp(_NIL_TYPE_);
static _TKN_TYPE_ scan_Xop(_NIL_TYPE_);

/* private variables */

static _CHA_TYPE_ scan_ch    = 0;
static _STR_TYPE_ scan_text  = 0;
static _SGN_TYPE_ scan_mark  = 0;
static _POS_TYPE_ scan_index = 0;
static _POS_TYPE_ scan_start = 0;
static _POS_TYPE_ scan_stop  = 0;

/* changed xop into qum, exm and sir */
static const scan_fun_index scan_char_tab[]  
   /*NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI */
  = {Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Eol,Wsp,Wsp,
   /*DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US */
     Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,Wsp,
   /*     !   "   #   $   %   &   '   (   )   *   +   ,   -   .   / */
     Wsp,Exm,Quo,Rop,Aop,Aop,Mop,Apo,Lpr,Rpr,Mop,Pls,Com,Mns,Per,Mop,
   /* 0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ? */
     Dgt,Dgt,Dgt,Dgt,Dgt,Dgt,Dgt,Dgt,Dgt,Dgt,Col,Smc,Rop,Eql,Rop,Qum,
   /* @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O */
     Cat,Ltr,Ltr,Ltr,Ltr,Exp,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,
   /* P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _ */
     Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Lbr,Mop,Rbr,Sir,Ltr,
   /* `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o */
     Bkq,Ltr,Ltr,Ltr,Ltr,Exp,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,
   /* p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL*/
     Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Ltr,Lbc,Aop,Rbc,Aop,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,
   /*                                                               */
     Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill,Ill};
     
static scan_fun *scan_fun_tab[] = { scan_Aop,
			                              scan_Apo,
			                              scan_Bkq,
			                              scan_Cat,
			                              scan_Col,
			                              scan_Com,
			                              scan_Dgt,
			                              scan_Wsp,
			                              scan_Rop,
			                              scan_Ltr,
			                              scan_Ill,
			                              scan_Lbc,
			                              scan_Lbr,
			                              scan_Lpr,
			                              scan_Ltr,
			                              scan_Aop,
			                              scan_Mop,
			                              scan_Ill,
			                              scan_Aop,
			                              scan_Quo,
			                              scan_Rbc,
			                              scan_Rbr,
			                              scan_Rop,
			                              scan_Rpr,
			                              scan_Smc,
			                              scan_Wsp,
			                              scan_Xop,
			                              scan_Xop,   /* added */
			                              scan_Xop }; /* added */

static const _UNS_TYPE_ operator_mask = (1<<Aop)+(1<<Eql)+(1<<Mns)+
                                        (1<<Mop)+(1<<Pls)+(1<<Rop)+
                                        (1<<Qum)+(1<<Exm)+(1<<Sir);

static const _UNS_TYPE_     name_mask = (1<<Dgt)+(1<<Exp)+(1<<Ltr);

static const _UNS_TYPE_  eol_apo_mask = (1<<Apo)+(1<<Eol);

static const _UNS_TYPE_      apo_mask = (1<<Apo);

static const _UNS_TYPE_  eol_bkq_mask = (1<<Bkq)+(1<<Eol);

static const _UNS_TYPE_      bkq_mask = (1<<Bkq);

static const _UNS_TYPE_  eol_quo_mask = (1<<Eol)+(1<<Quo);

static const _UNS_TYPE_      quo_mask = (1<<Quo);

static const _UNS_TYPE_    digit_mask = (1<<Dgt);

static const _UNS_TYPE_     sign_mask = (1<<Mns)+(1<<Pls);

static const _UNS_TYPE_   period_mask = (1<<Per);

static const _UNS_TYPE_ exponent_mask = (1<<Exp);

static const _UNS_TYPE_    equal_mask = (1<<Eql);

static const _UNS_TYPE_      wsp_mask = (1<<Eol)+(1<<Wsp);

static const _UNS_TYPE_      col_mask = (1<<Col); /* added */

static const _UNS_TYPE_      exm_mask = (1<<Exm); /* added */

static const _UNS_TYPE_      qum_mask = (1<<Qum); /* added */

static const _UNS_TYPE_      rpr_mask = (1<<Rpr); /* added */

static const _UNS_TYPE_      rbc_mask = (1<<Rbc); /* added */

/* private functions */

static _NIL_TYPE_ scan_store_next_ch(_NIL_TYPE_)
 { _TEXT_BUF_[scan_index++] = scan_ch; 
   if (scan_index == _BUF_SIZE_)
     _scan_error_(_BUF_ERROR_);
   else
     SCAN_NEXT_CH(); }
   
static _NIL_TYPE_ scan_terminate_text(_NIL_TYPE_)
 { _TEXT_BUF_[scan_index] = '\0';
   scan_index = 0; }

static _NIL_TYPE_ scan_operator(_NIL_TYPE_) 
 { do
     scan_store_next_ch();
   while (SCAN_CHECK(operator_mask));
   scan_terminate_text(); }
  
static _NIL_TYPE_ scan_name(_NIL_TYPE_)
 { do
     scan_store_next_ch();
   while (SCAN_CHECK(name_mask));
   scan_terminate_text(); }
  
static _TKN_TYPE_ scan_exponent(_NIL_TYPE_)
 { scan_store_next_ch();
   if (SCAN_CHECK(sign_mask))
     scan_store_next_ch();
   if (SCAN_CHECK(digit_mask))
     do 
       scan_store_next_ch();
     while (SCAN_CHECK(digit_mask));
   else
     _scan_error_(_DIG_ERROR_);
   scan_terminate_text();  
   return _FRC_TOKEN_; }

static _TKN_TYPE_ scan_fraction(_NIL_TYPE_)
 { scan_store_next_ch();
   if (SCAN_CHECK(digit_mask))
     do 
       scan_store_next_ch();
     while (SCAN_CHECK(digit_mask));
   else
     _scan_error_(_DIG_ERROR_);
   if (SCAN_CHECK(exponent_mask))
     return scan_exponent();
   else
     { scan_terminate_text(); 
       return _FRC_TOKEN_; }}

static _TKN_TYPE_ scan_number(_NIL_TYPE_)
 { do
     scan_store_next_ch();
   while (SCAN_CHECK(digit_mask));
   if (SCAN_CHECK(period_mask))
     return scan_fraction();
   else
     if (SCAN_CHECK(exponent_mask))
       return scan_exponent(); 
     else
       { scan_terminate_text();
         return _NBR_TOKEN_; }}
        
static _TKN_TYPE_ scan_Aop(_NIL_TYPE_)
 { scan_operator();
   return _AOP_TOKEN_; }
  
static _TKN_TYPE_ scan_Apo(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   while (SCAN_UNCHECK(eol_apo_mask))
     scan_store_next_ch();
   if (SCAN_CHECK(apo_mask))
     SCAN_NEXT_CH();
   else
     _scan_error_(_TXT_ERROR_);
   scan_terminate_text();
   return _TXT_TOKEN_; }
  
static _TKN_TYPE_ scan_Bkq(_NIL_TYPE_)
 { do
     SCAN_NEXT_CH();
   while (SCAN_UNCHECK(eol_bkq_mask));
   if (SCAN_CHECK(bkq_mask)) 
     SCAN_NEXT_CH();
   return _scan_(); }
  
static _TKN_TYPE_ scan_Cat(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   return _CAT_TOKEN_; }
  
static _TKN_TYPE_ scan_Col(_NIL_TYPE_) 
 { SCAN_NEXT_CH();
   if (SCAN_CHECK(equal_mask))
     { SCAN_NEXT_CH();
       return _CEQ_TOKEN_; }
   else if (SCAN_CHECK(exm_mask)) /* added */
     { SCAN_NEXT_CH();
       if (!SCAN_CHECK(col_mask))
    	   _scan_error_(_ILL_ERROR_);
       SCAN_NEXT_CH();
       return _PRG_TOKEN_; }
   else if (SCAN_CHECK(qum_mask))  /* added */
     { SCAN_NEXT_CH();
       if (!SCAN_CHECK(col_mask))
  	       _scan_error_(_ILL_ERROR_);
       SCAN_NEXT_CH();
       return _PRA_TOKEN_; }
   else if (SCAN_CHECK(rpr_mask))  /* added */
     { SCAN_NEXT_CH();
       return _PRE_TOKEN_; }
   else if (SCAN_CHECK(rbc_mask))  /* added */
     { SCAN_NEXT_CH();
       return _SPE_TOKEN_; }
   else
     return _COL_TOKEN_; }
  
static _TKN_TYPE_ scan_Com(_NIL_TYPE_) 
 { SCAN_NEXT_CH();
   return _COM_TOKEN_; }

static _TKN_TYPE_ scan_Dgt(_NIL_TYPE_)
 { return scan_number(); }

static _TKN_TYPE_ scan_Ill(_NIL_TYPE_)
 { _scan_error_(_ILL_ERROR_);
   return _END_TOKEN_; }
  
static _TKN_TYPE_ scan_Lbc(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   if (SCAN_CHECK(col_mask)) /* added */
     { SCAN_NEXT_CH();
       return _SPB_TOKEN_; }
   return _LBC_TOKEN_; }
  
static _TKN_TYPE_ scan_Lbr(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   return _LBR_TOKEN_; }
  
static _TKN_TYPE_ scan_Lpr(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   if (SCAN_CHECK(col_mask)) /* added */
     { SCAN_NEXT_CH();
       return _PRB_TOKEN_; }
   return _LPR_TOKEN_; }
  
static _TKN_TYPE_ scan_Ltr(_NIL_TYPE_)
 { scan_name();
   return _NAM_TOKEN_; }
  
static _TKN_TYPE_ scan_Mop(_NIL_TYPE_)
 { scan_operator();
   return _MOP_TOKEN_; }
  
static _TKN_TYPE_ scan_Quo(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   while (SCAN_UNCHECK(eol_quo_mask))
     scan_store_next_ch();
   if (SCAN_CHECK(quo_mask))
     SCAN_NEXT_CH();
   else
     _scan_error_(_TXT_ERROR_);
   scan_terminate_text();
   return _TXT_TOKEN_; }
  
static _TKN_TYPE_ scan_Rbc(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   return _RBC_TOKEN_; }
    
static _TKN_TYPE_ scan_Rbr(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   return _RBR_TOKEN_; }
    
static _TKN_TYPE_ scan_Rop(_NIL_TYPE_)
 { scan_operator();
   return _ROP_TOKEN_; }
  
static _TKN_TYPE_ scan_Rpr(_NIL_TYPE_)
 { SCAN_NEXT_CH();
   return _RPR_TOKEN_; }
  
static _TKN_TYPE_ scan_Smc(_NIL_TYPE_) 
 { SCAN_NEXT_CH();
   return _SMC_TOKEN_; }
  
static _TKN_TYPE_ scan_Wsp(_NIL_TYPE_)
 { do
     SCAN_NEXT_CH();
   while (SCAN_CHECK(wsp_mask));
   if (scan_ch) 
     return _scan_();
   else
     return _END_TOKEN_; }
  
static _TKN_TYPE_ scan_Xop(_NIL_TYPE_)
 { scan_operator();
   return _XOP_TOKEN_; }
  
/* public functions */

_NIL_TYPE_ _scan_init_(const _STR_TYPE_ str, 
                       const _SGN_TYPE_ tst)
 { scan_start = 0;
   scan_stop = 0;
   scan_index = 0;
   scan_mark = tst;
   scan_text = str;
   SCAN_NEXT_CH(); }

_TKN_TYPE_ _scan_(_NIL_TYPE_)
 { scan_fun_index index;
   if (scan_ch)
     { index = scan_char_tab[scan_ch];
       scan_start = scan_stop;  
       return (*scan_fun_tab[index])(); }
   else
     return _END_TOKEN_; }
      
_NIL_TYPE_ _scan_error_(const _RES_TYPE_ err)
 { if (scan_mark && scan_start)
     _mark_(scan_start-1, scan_stop-1);
   scan_index = 0;
   _error_(err); }

_SGN_TYPE_ _scan_number_(_NIL_TYPE_)
 { return atoi(_TEXT_BUF_); }

_FLO_TYPE_ _scan_fraction_(_NIL_TYPE_)
 { return atof(_TEXT_BUF_); }
   
_STR_TYPE_ _scan_string_(_NIL_TYPE_)
 { return _TEXT_BUF_; }
