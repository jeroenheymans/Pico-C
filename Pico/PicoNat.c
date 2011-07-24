/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*          Native functions         */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  VARIABLES                                                             */
/*                                                                        */
/*  void: <void>                                                          */ 
/*  eoln: char(13)                                                        */ 
/*                                                                        */
/*  ARITHMETIC                                                            */
/*                                                                        */
/*  +{nbr} : {nbr}                                                        */
/*  +{frc} : {frc}                                                        */
/*  {nbr}+{nbr} : {nbr+nbr}                                               */
/*  {nbr}+{frc} : {nbr+frc}                                               */
/*  {frc}+{nbr} : {frc+nbr}                                               */
/*  {frc}+{frc} : {frc+frc}                                               */
/*                                                                        */
/*  -{nbr} : {-nbr}                                                       */
/*  -{frc} : {-frc}                                                       */
/*  {nbr}-{nbr} : {nbr-nbr}                                               */
/*  {nbr}-{frc} : {nbr-frc}                                               */
/*  {frc}-{nbr} : {frc-nbr}                                               */
/*  {frc}-{frc} : {frc-frc}                                               */
/*                                                                        */
/*  {nbr}*{nbr} : {nbr*nbr}                                               */
/*  {nbr}*{frc} : {nbr*frc}                                               */
/*  {frc}*{nbr} : {frc*nbr}                                               */
/*  {frc}*{frc} : {frc*frc}                                               */
/*                                                                        */
/*  {nbr}/{nbr} : {(FRC)nbr/(FRC)nbr}                                     */
/*  {nbr}/{frc} : {(FRC)nbr/frc}                                          */
/*  {frc}/{nbr} : {frc/(FRC)nbr}                                          */
/*  {frc}/{frc} : {frc/frc}                                               */
/*                                                                        */
/*  {nbr}//{nbr} : {nbr/nbr}                                              */
/*                                                                        */
/*  {nbr}\\{nbr} : {nbr%nbr}                                              */
/*                                                                        */
/*  {nbr}^{nbr} : {pow(nbr,nbr)}                                          */
/*  {nbr}^{frc} : {pow(nbr,frc)}                                          */
/*  {frc}^{nbr} : {pow(frc,nbr)}                                          */
/*  {frc}^{frc} : {pow(frc,frc)}                                          */
/*                                                                        */
/*  RELATIONAL                                                            */
/*                                                                        */
/*  {nbr}<{nbr} : {(nbr<nbr)?{true} : {false}}                            */
/*  {nbr}<{frc} : {(nbr<frc)?{true} : {false}}                            */
/*  {frc}<{nbr} : {(frc<nbr)?{true} : {false}}                            */
/*  {frc}<{frc} : {(frc<frc)?{true} : {false}}                            */
/*  {txt}<{txt} : {(strcmp(txt,txt)<0)?{true} : {false}}                  */
/*                                                                        */
/*  {nbr}={nbr} : {(nbr==nbr)?{true} : {false}}                           */
/*  {nbr}={frc} : {(nbr==frc)?{true} : {false}}                           */
/*  {frc}={nbr} : {(frc==nbr)?{true} : {false}}                           */
/*  {frc}={frc} : {(frc==frc)?{true} : {false}}                           */
/*  {txt}={txt} : {(strcmp(txt,txt)==0)?{true} : {false}}                 */
/*                                                                        */
/*  {nbr}>{nbr} : {(nbr>nbr)?{true} : {false}}                            */
/*  {nbr}>{frc} : {(nbr>frc)?{true} : {false}}                            */
/*  {frc}>{nbr} : {(frc>nbr)?{true} : {false}}                            */
/*  {frc}>{frc} : {(frc>frc)?{true} : {false}}                            */
/*  {txt}>{txt} : {(strcmp(txt,txt)>0)?{true} : {false}}                  */
/*                                                                        */
/*  equivalent({any},{any}) : {(any==any)?{true} : {false}}               */
/*                                                                        */
/*  CONVERSION                                                            */
/*                                                                        */
/*  trunc({frc}) : {(NBR)frc}                                             */
/*                                                                        */
/*  abs({nbr}) : {abs(nbr)}                                               */
/*  abs({frc}) : {fabs(frc)}                                              */
/*                                                                        */
/*  char({nbr}) : {(TXT)nbr}                                              */
/*  ord({chr})  : {(NBR)chr}                                              */
/*                                                                        */
/*  random() : {rand()}                                                   */
/*                                                                        */
/*  number({txt}) : {string_to_number(nbr)}                               */
/*                                                                        */
/*  text({any}) : {display_to_text(any)}                                  */
/*                                                                        */
/*  TRANSCEDENTAL                                                         */
/*                                                                        */
/*  sqrt({nbr}) : {sqrt(nbr)}                                             */
/*  sqrt({frc}) : {sqrt(frc)}                                             */
/*                                                                        */
/*  sin({nbr}) : {sin(nbr)}                                               */
/*  sin({frc}) : {sin(frc)}                                               */
/*                                                                        */
/*  cos({nbr}) : {cos(nbr)}                                               */
/*  cos({frc}) : {cos(frc)}                                               */
/*                                                                        */
/*  tan({nbr}) : {tan(nbr)}                                               */
/*  tan({frc}) : {tan(frc)}                                               */
/*                                                                        */
/*  arcsin({nbr}) : {asin(nbr)}                                           */
/*  arcsin({frc}) : {asin(frc)}                                           */
/*                                                                        */
/*  arccos({nbr}) : {acos(nbr)}                                           */
/*  arccos({frc}) : {acos(frc)}                                           */
/*                                                                        */
/*  arctan({nbr}) : {atan(nbr)}                                           */
/*  arctan({frc}) : {atan(frc)}                                           */
/*                                                                        */
/*  exp({nbr}) : {exp(nbr)}                                               */
/*  exp({frc}) : {exp(frc)}                                               */
/*                                                                        */
/*  log({nbr}) : {log(nbr)}                                               */
/*  log({frc}) : {log(frc)}                                               */
/*                                                                        */
/*  TEXT                                                                  */
/*                                                                        */
/*  explode({txt}) : {str_to_tab(txt)}                                    */
/*                                                                        */
/*  implode({tab}) : {tab_to_str(tab)}                                    */
/*                                                                        */
/*  size({txt}) : {size(txt)} [see TABLE]                                 */
/*                                                                        */
/*  {txt}+{txt} : {txt+txt} [see ARITHMETIC]                              */
/*                                                                        */
/*  IDENTITY                                                              */
/*                                                                        */
/*  is_number({any}) : {(tag(any)==NBR)?{true} : {false}}                 */
/*                                                                        */
/*  is_fraction({any}) : {(tag(any)==FRC)?{true} : {false}}               */
/*                                                                        */
/*  is_text({any}) : {(tag(any)==TXT)?{true} : {false}}                   */
/*                                                                        */
/*  is_function({any}) : {(tag(any)==FUN)?{true}:{false}}                 */
/*                                                                        */
/*  is_table({any}) : {(tag(any)==TAB)?{true}:{false}}                    */
/*                                                                        */
/*  is_void({any}) : {(tag(any)==VOI)?{true}:{false}}                     */
/*                                                                        */
/*  TABLE                                                                 */
/*                                                                        */
/*  size({tab}) : {size(tab)}                                             */
/*                                                                        */
/*  tab@arg : arg                                                         */
/*                                                                        */
/*  INTERACTION                                                           */
/*                                                                        */
/*  display@tab:{do(show(tab)),{void}}                                    */
/*                                                                        */
/*  accept():{read_string()}                                              */
/*                                                                        */
/*  BOOLEAN                                                               */
/*                                                                        */
/*  true(then(), else()) : then()                                         */
/*                                                                        */
/*  false(then(), else()) : else()                                        */
/*                                                                        */
/*  and(left, right()) : left(right(), false)                             */
/*                                                                        */
/*  or(left, right()) : left(true, right())                               */
/*                                                                        */
/*  not(pred) : pred(false, true)                                         */
/*                                                                        */
/*  STRUCTURE                                                             */
/*                                                                        */
/*  begin@tab : tab[size(tab)]                                            */
/*                                                                        */
/*  call(exp(cont)) : exp(env_capture())                                  */
/*                                                                        */
/*  continue(cont, value) : { env_restore(cont); return value; }          */
/*                                                                        */
/*  if(cond, then(), else()) : cond(then(), else())                       */
/*                                                                        */
/*  while(cond(), body())                                                 */
/*      : begin(loop(value, boolean)                                      */
/*                : boolean(loop(body(), cond()), value),                 */
/*            loop(void, cond())                                          */
/*                                                                        */
/*  until(cond(), body())                                                 */
/*      : begin(loop(value, boolean)                                      */
/*                : boolean(value, loop(body(), cond())),                 */
/*            loop(body(), cond())                                        */
/*                                                                        */
/*  for(init, incr(), cond(), body())                                     */
/*      : begin(loop(value, boolean)                                      */
/*                : boolean(loop(begin(body(), incr()), cond()), value),  */
/*            loop(void, cond())                                          */
/*                                                                        */
/*                                                                        */
/*  METALEVEL                                                             */
/*                                                                        */
/*  load():         {_print_(_eval_(_read_(load_string())))}              */
/*                                                                        */
/*  read({txt}):    {_read_(txt})}                                        */
/*                                                                        */
/*  eval({exp}):    {_eval_(exp)}                                         */
/*                                                                        */
/*  print({exp}):   {_print_(exp)}                                        */
/*                                                                        */
/*  tag({any}):     {_GET_TAG_(any)}                                      */
/*                                                                        */
/*  make({tag}):    {make(tag)}                                           */
/*                                                                        */
/*  ESCAPE                                                                */
/*                                                                        */
/*  escape(exp):    {_ESC_ = exp}                                         */
/*                                                                        */
/*  error(txt):     {_error_(txt)}                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoEnv.h"
#include "PicoRea.h"
#include "PicoPri.h"
#include "PicoEva.h"
#include "PicoNat.h"

/* private constants */

#define NATIVE_SIZE 60 /* 60 native functions (is_process added) */

#define CAL _eval_CAL_
#define EVL _eval_EXP_
#define RDD _read_EXP_
#define PRT _print_EXP_

   /*--STRINGS--------*/
#define nwl_STR "\n"
#define nul_STR ""
   /*--VARIABLES------*/
#define eol_STR "eoln"
#define voi_STR "void"
   /*--PARAMETERS-----*/
#define cnt_STR "cont"
   /*--ARITHMETIC-----*/
#define add_STR "+" 
#define sub_STR "-" 
#define mul_STR "*"  
#define div_STR "/" 
#define idv_STR "/""/" 
#define rem_STR "\\""\\" 
#define pow_STR "^" 
   /*--RELATIONAL-----*/
#define lss_STR "<" 
#define eql_STR "=" 
#define grt_STR ">" 
#define eqv_STR "equivalent" 
   /*--CONVERSION-----*/
#define trn_STR "trunc" 
#define abs_STR "abs"  
#define chr_STR "char"  
#define ord_STR "ord"  
#define rnd_STR "random"  
#define num_STR "number"  
#define tex_STR "text"  
   /*--TRANSCENDENTAL-*/
#define sqt_STR "sqrt" 
#define sin_STR "sin"  
#define cos_STR "cos"  
#define tan_STR "tan"  
#define asn_STR "arcsin"  
#define acs_STR "arccos"  
#define atn_STR "arctan" 
#define epw_STR "exp" 
#define log_STR "log" 
   /*--STRING---------*/
#define epl_STR "explode" 
#define ipl_STR "implode" 
   /*--IDENTITY  */
#define nbr_STR "is_number" 
#define frc_STR "is_fraction" 
#define txt_STR "is_text" 
#define fun_STR "is_function" 
#define tbl_STR "is_table" 
#define vdd_STR "is_void" 
#define pro_STR "is_process" /* added */
   /*--TABLE----------*/
#define siz_STR "size" 
#define tab_STR "tab" 
   /*--INTERACTION----*/
#define dsp_STR "display" 
#define acp_STR "accept" 
   /*--BOOLEAN--------*/
#define trr_STR "true" 
#define fls_STR "false" 
#define and_STR "and" 
#define orr_STR "or" 
#define not_STR "not" 
   /*--STRUCTURE------*/
#define beg_STR "begin" 
#define cll_STR "call" 
#define con_STR "continue" 
#define iff_STR "if" 
#define whi_STR "while" 
#define unt_STR "until" 
#define for_STR "for" 
   /*--METALEVEL------*/
#define lod_STR "load" 
#define rea_STR "read" 
#define eva_STR "eval" 
#define pri_STR "print" 
#define tag_STR "tag" 
#define mak_STR "make" 
   /*--ESCAPE---------*/
#define esc_STR "interrupt"
#define err_STR "error"

/* private prototypes */

   /*--ARITHMETIC-----*/
static _NIL_TYPE_ ADD(_NIL_TYPE_); /* + */
static _NIL_TYPE_ SUB(_NIL_TYPE_); /* - */
static _NIL_TYPE_ MUL(_NIL_TYPE_); /* * */
static _NIL_TYPE_ DIV(_NIL_TYPE_); /* / */
static _NIL_TYPE_ IDV(_NIL_TYPE_);
static _NIL_TYPE_ REM(_NIL_TYPE_);
static _NIL_TYPE_ POW(_NIL_TYPE_);
   /*--RELATIONAL-----*/
static _NIL_TYPE_ LSS(_NIL_TYPE_);
static _NIL_TYPE_ EQL(_NIL_TYPE_);
static _NIL_TYPE_ GRT(_NIL_TYPE_);
static _NIL_TYPE_ EQV(_NIL_TYPE_);
   /*--CONVERSION-----*/
static _NIL_TYPE_ TRN(_NIL_TYPE_);
static _NIL_TYPE_ ABS(_NIL_TYPE_);
static _NIL_TYPE_ CHR(_NIL_TYPE_);
static _NIL_TYPE_ ORD(_NIL_TYPE_);
static _NIL_TYPE_ RND(_NIL_TYPE_);
static _NIL_TYPE_ NUM(_NIL_TYPE_);
static _NIL_TYPE_ TEX(_NIL_TYPE_);
   /*--TRANSCENDENTAL-*/
static _NIL_TYPE_ SQT(_NIL_TYPE_);
static _NIL_TYPE_ SIN(_NIL_TYPE_);
static _NIL_TYPE_ COS(_NIL_TYPE_);
static _NIL_TYPE_ TAN(_NIL_TYPE_);
static _NIL_TYPE_ ASN(_NIL_TYPE_);
static _NIL_TYPE_ ACS(_NIL_TYPE_);
static _NIL_TYPE_ ATN(_NIL_TYPE_);
static _NIL_TYPE_ EPW(_NIL_TYPE_);
static _NIL_TYPE_ LOG(_NIL_TYPE_);
   /*--STRING---------*/
static _NIL_TYPE_ EPL(_NIL_TYPE_);
static _NIL_TYPE_ IPL(_NIL_TYPE_);
   /*--IDENTITY-------*/
static _NIL_TYPE_ NBR(_NIL_TYPE_);
static _NIL_TYPE_ FRC(_NIL_TYPE_);
static _NIL_TYPE_ TXT(_NIL_TYPE_);
static _NIL_TYPE_ FUN(_NIL_TYPE_);
static _NIL_TYPE_ TBL(_NIL_TYPE_);
static _NIL_TYPE_ VDD(_NIL_TYPE_);
static _NIL_TYPE_ PRO(_NIL_TYPE_); /* added */
static _NIL_TYPE_ PRO1(_NIL_TYPE_); /* added */
   /*--TABLE----------*/
static _NIL_TYPE_ SIZ(_NIL_TYPE_);
static _NIL_TYPE_ TAB(_NIL_TYPE_);
   /*--INTERACTION----*/
static _NIL_TYPE_ DSP(_NIL_TYPE_);
static _NIL_TYPE_ ACP(_NIL_TYPE_);
   /*--BOOLEAN--------*/
static _NIL_TYPE_ TRR(_NIL_TYPE_);
static _NIL_TYPE_ FLS(_NIL_TYPE_);
static _NIL_TYPE_ AND(_NIL_TYPE_);
static _NIL_TYPE_ ORR(_NIL_TYPE_);
static _NIL_TYPE_ NOT(_NIL_TYPE_);
   /*--STRUCTURE------*/
static _NIL_TYPE_ BEG(_NIL_TYPE_);
static _NIL_TYPE_ CLL(_NIL_TYPE_);
static _NIL_TYPE_ CON(_NIL_TYPE_);
static _NIL_TYPE_ IFF(_NIL_TYPE_);
static _NIL_TYPE_ WHI(_NIL_TYPE_);
static _NIL_TYPE_ UNT(_NIL_TYPE_);
static _NIL_TYPE_ FOR(_NIL_TYPE_);
   /*--METALEVEL------*/
static _NIL_TYPE_ LOD(_NIL_TYPE_);
static _NIL_TYPE_ REA(_NIL_TYPE_);
static _NIL_TYPE_ EVA(_NIL_TYPE_);
static _NIL_TYPE_ PRI(_NIL_TYPE_);
static _NIL_TYPE_ TAG(_NIL_TYPE_);
static _NIL_TYPE_ MAK(_NIL_TYPE_);
   /*--ESCAPE---------*/
static _NIL_TYPE_ ESC(_NIL_TYPE_);
static _NIL_TYPE_ ERR(_NIL_TYPE_);
   /*--AUXILIARY--*---*/
static _NIL_TYPE_ ADB(_NIL_TYPE_);
static _NIL_TYPE_ ADU(_NIL_TYPE_);
static _NIL_TYPE_ SBB(_NIL_TYPE_);
static _NIL_TYPE_ SBU(_NIL_TYPE_);
static _NIL_TYPE_ MLB(_NIL_TYPE_);
static _NIL_TYPE_ DVB(_NIL_TYPE_);
static _NIL_TYPE_ IDB(_NIL_TYPE_);
static _NIL_TYPE_ RMB(_NIL_TYPE_);
static _NIL_TYPE_ PWB(_NIL_TYPE_);
static _NIL_TYPE_ LSB(_NIL_TYPE_);
static _NIL_TYPE_ EQB(_NIL_TYPE_);
static _NIL_TYPE_ GRB(_NIL_TYPE_);
static _NIL_TYPE_ EVB(_NIL_TYPE_);
static _NIL_TYPE_ TRU(_NIL_TYPE_);
static _NIL_TYPE_ ABU(_NIL_TYPE_);
static _NIL_TYPE_ CHU(_NIL_TYPE_);
static _NIL_TYPE_ ORU(_NIL_TYPE_);
static _NIL_TYPE_ NMU(_NIL_TYPE_);
static _NIL_TYPE_ TEU(_NIL_TYPE_);
static _NIL_TYPE_ SQU(_NIL_TYPE_);
static _NIL_TYPE_ SNU(_NIL_TYPE_);
static _NIL_TYPE_ CSU(_NIL_TYPE_);
static _NIL_TYPE_ TNU(_NIL_TYPE_);
static _NIL_TYPE_ ASU(_NIL_TYPE_);
static _NIL_TYPE_ ACU(_NIL_TYPE_);
static _NIL_TYPE_ ATU(_NIL_TYPE_);
static _NIL_TYPE_ EPU(_NIL_TYPE_);
static _NIL_TYPE_ LGU(_NIL_TYPE_);
static _NIL_TYPE_ EPZ(_NIL_TYPE_);
static _NIL_TYPE_ IPZ(_NIL_TYPE_);
static _NIL_TYPE_ NBU(_NIL_TYPE_);
static _NIL_TYPE_ FRU(_NIL_TYPE_);
static _NIL_TYPE_ TXU(_NIL_TYPE_);
static _NIL_TYPE_ FNU(_NIL_TYPE_);
static _NIL_TYPE_ TBU(_NIL_TYPE_);
static _NIL_TYPE_ VDU(_NIL_TYPE_);
static _NIL_TYPE_ SZU(_NIL_TYPE_);
static _NIL_TYPE_ TBX(_NIL_TYPE_);
static _NIL_TYPE_ DSX(_NIL_TYPE_);
static _NIL_TYPE_ DSY(_NIL_TYPE_);
static _NIL_TYPE_ DSZ(_NIL_TYPE_);
static _NIL_TYPE_ ANC(_NIL_TYPE_);
static _NIL_TYPE_ ORC(_NIL_TYPE_);
static _NIL_TYPE_ NTC(_NIL_TYPE_);
static _NIL_TYPE_ BXG(_NIL_TYPE_);
static _NIL_TYPE_ CLX(_NIL_TYPE_);
static _NIL_TYPE_ COX(_NIL_TYPE_);
static _NIL_TYPE_ IFC(_NIL_TYPE_);
static _NIL_TYPE_ WHC(_NIL_TYPE_);
static _NIL_TYPE_ WHE(_NIL_TYPE_);
static _NIL_TYPE_ UNE(_NIL_TYPE_);
static _NIL_TYPE_ UNC(_NIL_TYPE_);
static _NIL_TYPE_ FRS(_NIL_TYPE_);
static _NIL_TYPE_ FRX(_NIL_TYPE_);
static _NIL_TYPE_ FRE(_NIL_TYPE_);
static _NIL_TYPE_ FRI(_NIL_TYPE_);
static _NIL_TYPE_ LOU(_NIL_TYPE_);
static _NIL_TYPE_ REU(_NIL_TYPE_);
static _NIL_TYPE_ EVU(_NIL_TYPE_);
static _NIL_TYPE_ PRU(_NIL_TYPE_);
static _NIL_TYPE_ TAU(_NIL_TYPE_);
static _NIL_TYPE_ MKU(_NIL_TYPE_);
static _NIL_TYPE_ SWU(_NIL_TYPE_);
static _NIL_TYPE_ ERU(_NIL_TYPE_);

/* private variables */

static const _CNT_TYPE_ FUN_tab[] =
   /*--ARITHMETIC-----*/
 { ADD,
   SUB,
   MUL,
   DIV,
   IDV,
   REM,
   POW,
   /*--RELATIONAL-----*/
   LSS,
   EQL,
   GRT,
   EQV,
   /*--CONVERSION-----*/
   TRN,
   ABS,
   CHR,
   ORD,
   RND,
   NUM,
   TEX,
   /*--TRANSCENDENTAL-*/
   SQT,
   SIN,
   COS,
   TAN,
   ASN,
   ACS,
   ATN,
   EPW,
   LOG,
   /*--STRING---------*/
   EPL,
   IPL,
   /*--IDENTITY-------*/
   NBR,
   FRC,
   TXT,
   FUN,
   TBL,
   VDD,
   PRO, /* added */
   /*--TABLE----------*/
   SIZ,
   TAB,
   /* INTERACTION-----*/
   DSP,
   ACP,
   /*--BOOLEAN--------*/
   TRR,
   FLS,
   AND,
   ORR,
   NOT,
   /*--STRUCTURE------*/
   BEG,
   CLL,
   CON,
   IFF,
   WHI,
   UNT,
   FOR,
   /*--METALEVEL------*/
   LOD,
   REA,
   EVA,
   PRI,
   TAG,
   MAK, 
   /*--ESCAPE---------*/
   ESC,
   ERR };

static const _STR_TYPE_ STR_tab[] =
   /*--ARITHMETIC-----*/
 { add_STR, 
   sub_STR, 
   mul_STR, 
   div_STR, 
   idv_STR, 
   rem_STR, 
   pow_STR, 
   /*--RELATIONAL-----*/
   lss_STR, 
   eql_STR, 
   grt_STR, 
   eqv_STR, 
   /*--CONVERSION-----*/
   trn_STR, 
   abs_STR, 
   chr_STR, 
   ord_STR, 
   rnd_STR, 
   num_STR, 
   tex_STR, 
   /*--TRANSCENDENTAL-*/
   sqt_STR,
   sin_STR, 
   cos_STR, 
   tan_STR, 
   asn_STR, 
   acs_STR, 
   atn_STR, 
   epw_STR, 
   log_STR, 
   /*--STRING---------*/
   epl_STR, 
   ipl_STR, 
   /*--IDENTITY-------*/
   nbr_STR, 
   frc_STR, 
   txt_STR, 
   fun_STR,
   tbl_STR, 
   vdd_STR, 
   pro_STR, /* added */
   /*--TABLE----------*/
   siz_STR,  
   tab_STR, 
   /*--INTERACTION----*/
   dsp_STR, 
   acp_STR, 
   /*--BOOLEAN--------*/
   trr_STR, 
   fls_STR, 
   and_STR, 
   orr_STR, 
   not_STR, 
   /*--STRUCTURE------*/
   beg_STR, 
   cll_STR,
   con_STR,
   iff_STR, 
   whi_STR,  
   unt_STR, 
   for_STR,
   /*--METALEVEL------*/
   lod_STR,
   rea_STR,
   eva_STR,
   pri_STR,
   tag_STR,
   mak_STR,
   /*--ESCAPE---------*/
   esc_STR,
   err_STR };

/* public variables */

_EXP_TYPE_ _BEGIN_;
_EXP_TYPE_ _CONT_;
_EXP_TYPE_ _EMPTY_;
_EXP_TYPE_ _EOLN_;
_EXP_TYPE_ _ESC_;
_EXP_TYPE_ _FALSE_;
_EXP_TYPE_ _NULL_;
_EXP_TYPE_ _ONE_;
_EXP_TYPE_ _TAB_;
_EXP_TYPE_ _TRUE_;
_EXP_TYPE_ _VOID_;
_EXP_TYPE_ _ZERO_;

/* private functions */

/*------------------------------------------------------------------------*/
/*  swp                                                                   */
/*     expr-stack: [... ... ... ... EVL VAL] -> [... ... ... ... VAL EVL] */
/*     cont-stack: [... ... ... ... ... swp] -> [... ... ... ... ... EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ swp(_NIL_TYPE_)
 { _EXP_TYPE_ val, exp;
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(exp);
   _stk_poke_EXP_(val);
   _stk_push_EXP_(exp);
   _stk_poke_CNT_(EVL); }
   
/*------------------------------------------------------------------------*/
/*  una                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... una] -> [... ... ... ... cnt EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ una(const _CNT_TYPE_ cnt,
	                    const _STR_TYPE_ str)
 { _EXP_TYPE_ arg, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 1)
		 { exp = _ag_get_TAB_EXP_(arg, 1);
		   _stk_poke_EXP_(exp);
		   _stk_poke_CNT_(cnt);
		   _stk_push_CNT_(EVL); }
	 else
     _error_str_(_NMA_ERROR_, str); }

/*------------------------------------------------------------------------*/
/*  bin                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EXP EXP] */
/*     cont-stack: [... ... ... ... ... bin] -> [... ... ... cnt swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ bin(const _CNT_TYPE_ cnt,
                      const _STR_TYPE_ str)
 { _EXP_TYPE_ arg, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
		 { exp = _ag_get_TAB_EXP_(arg, 2);
		   _stk_poke_EXP_(exp);
		   exp = _ag_get_TAB_EXP_(arg, 1);
		   _stk_push_EXP_(exp);
		   _stk_poke_CNT_(cnt); 
		   _stk_push_CNT_(swp); 
		   _stk_push_CNT_(EVL); }
   else
     _error_str_(_NMA_ERROR_, str); }

/*------------------------------------------------------------------------*/
/*  ubi                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... ubi] -> [... ... ... ... cnu EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EXP EXP] */
/*     cont-stack: [... ... ... ... ... ubi] -> [... ... ... cnb swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ubi(const _CNT_TYPE_ cnu,
                      const _CNT_TYPE_ cnb,
                      const _STR_TYPE_ str)
 { _EXP_TYPE_ arg, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   switch (siz)
    { case 1:
        exp = _ag_get_TAB_EXP_(arg, 1);
        _stk_poke_EXP_(exp);
        _stk_poke_CNT_(cnu); 
        _stk_push_CNT_(EVL);
        return;
      case 2:
        exp = _ag_get_TAB_EXP_(arg, 2);
        _stk_poke_EXP_(exp);
        exp = _ag_get_TAB_EXP_(arg, 1);
        _stk_push_EXP_(exp);
        _stk_poke_CNT_(cnb); 
        _stk_push_CNT_(swp); 
        _stk_push_CNT_(EVL); 
        return; }
   _error_str_(_NMA_ERROR_, str); }
   
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*-----------------A R I T H M E T I C    O P E R A T O R S---------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  ADD                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... ADD] -> [... ... ... ADB swp EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ADD] -> [... ... ... ... ADU EVL] */
/*------------------------------------------------------------------------*/
   
static _NIL_TYPE_ ADD(_NIL_TYPE_)
 { ubi(ADU, ADB, add_STR); }

/*------------------------------------------------------------------------*/
/*  ADU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ADU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ADU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   if ((tag != _NBR_TAG_) && (tag != _FRC_TAG_))
     _error_str_(_ATC_ERROR_, add_STR); }

/*------------------------------------------------------------------------*/
/*  ADB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ADB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ADB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _UNS_TYPE_ len;
   _FLP_TYPE_ frc_1, frc_2;
   _STR_TYPE_ str_1, str_2;
   _SGN_TYPE_ nbr_1, nbr_2, res;
   _FLO_TYPE_ flo;
   _mem_claim_();
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   res = nbr_1 + nbr_2;
                   if (labs(res) > _NBR_MAX_)
                     _error_str_(_NBR_ERROR_, add_STR);
                   _stk_poke_EXP_(_ag_make_NBR_(res));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = nbr_1 + *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _FRC_TAG_:
         { frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = *frc_1 + nbr_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = *frc_1 + *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _TXT_TAG_:
         { str_1 = _ag_get_TXT_(val_1);
           if (tag_2 == _TXT_TAG_) 
             { str_2 = _ag_get_TXT_(val_2);
               len = strlen(str_1)+strlen(str_2);
               if (len > _BUF_SIZE_)
                 _error_str_(_BUF_ERROR_, add_STR);
               strcpy(_TEXT_BUF_, str_1);
               strcat(_TEXT_BUF_, str_2);
               _mem_claim_STR_(_TEXT_BUF_);
               _stk_poke_EXP_(_ag_make_TXT_(_TEXT_BUF_));    
               return; }}}
   _error_str_(_ATC_ERROR_, add_STR); }

/*------------------------------------------------------------------------*/
/*  SUB                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... SUB] -> [... ... ... SBB swp EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... SUB] -> [... ... ... ... SBU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SUB(_NIL_TYPE_)
 { ubi(SBU, SBB, sub_STR); }
  
/*------------------------------------------------------------------------*/
/*  SBU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... SBU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SBU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _FLO_TYPE_ flo;
   _mem_claim_();
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           _stk_poke_EXP_(_ag_make_NBR_(-nbr));     
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = -(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, sub_STR); }
   
/*------------------------------------------------------------------------*/
/*  SBB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... SBB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SBB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _FLP_TYPE_ frc_1, frc_2;
   _SGN_TYPE_ nbr_1, nbr_2, res;
   _FLO_TYPE_ flo;
   _mem_claim_();
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   res = nbr_1 - nbr_2;
                   if (labs(res) > _NBR_MAX_)
                     _error_str_(_NBR_ERROR_, sub_STR);
                   _stk_poke_EXP_(_ag_make_NBR_(res));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = nbr_1 - *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _FRC_TAG_:
         { frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = *frc_1 - nbr_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = *frc_1 - *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}}}
   _error_str_(_ATC_ERROR_, sub_STR); }

/*------------------------------------------------------------------------*/
/*  MUL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... MUL] -> [... ... ... MLB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ MUL(_NIL_TYPE_)
 { bin(MLB, mul_STR); }
  
/*------------------------------------------------------------------------*/
/*  MLB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... MLB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ MLB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _SGN_TYPE_ res;
   _mem_claim_();
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = (_FLO_TYPE_)nbr_1 * (_FLO_TYPE_)nbr_2;
                   if (fabs(flo) > _NBR_MAX_)
                     _error_str_(_NBR_ERROR_, mul_STR);
                   res = (_SGN_TYPE_)flo;
                   _stk_poke_EXP_(_ag_make_NBR_(res));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = nbr_1 * *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _FRC_TAG_:
         { _FLP_TYPE_ frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = *frc_1 * nbr_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   flo = *frc_1 * *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}}}
   _error_str_(_ATC_ERROR_, mul_STR); }

/*------------------------------------------------------------------------*/
/*  DIV                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... DIV] -> [... ... ... DVB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DIV(_NIL_TYPE_)
 { bin(DVB, div_STR); }
  
/*------------------------------------------------------------------------*/
/*  DVB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... DVB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DVB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _mem_claim_();
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   if (nbr_2 == 0)
                     _error_str_(_ZDV_ERROR_, div_STR);
                   flo = (_FLO_TYPE_)nbr_1 / (_FLO_TYPE_)nbr_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (fabs(*frc_2) < _FRC_MIN_)
                     _error_str_(_ZDV_ERROR_, div_STR);
                   flo = nbr_1 / *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _FRC_TAG_:
         { _FLP_TYPE_ frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   if (nbr_2 == 0)
                     _error_str_(_ZDV_ERROR_, div_STR);
                   flo = *frc_1 / nbr_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (fabs(*frc_2) < _FRC_MIN_)
                     _error_str_(_ZDV_ERROR_, div_STR);
                   flo = *frc_1 / *frc_2;
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}}}
   _error_str_(_ATC_ERROR_, div_STR); }

/*------------------------------------------------------------------------*/
/*  IDV                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... IDV] -> [... ... ... IDB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IDV(_NIL_TYPE_)
 { bin(IDB, idv_STR); }

/*------------------------------------------------------------------------*/
/*  IDB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... IDB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IDB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   if ((tag_1 == _NBR_TAG_) && (tag_2 == _NBR_TAG_))
     { nbr_1 = _ag_get_NBR_(val_1);
       nbr_2 = _ag_get_NBR_(val_2);
       if (nbr_2 == 0)
         _error_str_(_ZDV_ERROR_, idv_STR);
       _stk_poke_EXP_(_ag_make_NBR_(nbr_1 / nbr_2));      
       return; }
   _error_str_(_ATC_ERROR_, idv_STR); }

/*------------------------------------------------------------------------*/
/*  REM                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... REM] -> [... ... ... RMB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ REM(_NIL_TYPE_)
 { bin(RMB, rem_STR); }

/*------------------------------------------------------------------------*/
/*  RMB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... RMB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ RMB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   if ((tag_1 == _NBR_TAG_) && (tag_2 == _NBR_TAG_))
     { nbr_1 = _ag_get_NBR_(val_1);
       nbr_2 = _ag_get_NBR_(val_2);
       if (nbr_2 == 0)
         _error_str_(_ZDV_ERROR_, rem_STR);
       _stk_poke_EXP_(_ag_make_NBR_(nbr_1 % nbr_2));      
       return; }
   _error_str_(_ATC_ERROR_, rem_STR); }

/*------------------------------------------------------------------------*/
/*  POW                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... POW] -> [... ... ... PWB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ POW(_NIL_TYPE_)
 { bin(PWB, pow_STR); }
  
/*------------------------------------------------------------------------*/
/*  PWB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... PWB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/             
             
static _NIL_TYPE_ PWB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc_1, frc_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _mem_claim_();
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
  _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = pow(nbr_1, nbr_2);
                   if (fabs(flo) >= _FRC_MAX_)
                     _error_str_(_INF_ERROR_, pow_STR);
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (nbr_1 < 0)
                     _error_str_(_NEG_ERROR_, pow_STR); 
                   flo = pow(nbr_1, *frc_2);
                   if (fabs(flo) >= _FRC_MAX_)
                     _error_str_(_INF_ERROR_, pow_STR);
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}
           break; }
       case _FRC_TAG_:
         { frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   flo = pow(*frc_1, nbr_2);
                   if (fabs(flo) >= _FRC_MAX_)
                     _error_str_(_INF_ERROR_, pow_STR);
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (*frc_1 < 0)
                     _error_str_(_NEG_ERROR_, pow_STR); 
                   flo = pow(*frc_1, *frc_2);
                   if (fabs(flo) >= _FRC_MAX_)
                     _error_str_(_INF_ERROR_, pow_STR);
                   _stk_poke_EXP_(_ag_make_FRC_(&flo));     
                   return; }}}}
   _error_str_(_ATC_ERROR_, pow_STR); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*----------------R E L A T I O N A L    O P E R A T O R S----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ compare(const _SGN_COMP_ nbr_op, 
                          const _FLO_COMP_ frc_op, 
                          const _STR_COMP_ str_op,
                          const _STR_TYPE_ str)
 { _EXP_TYPE_ val_1, val_2;
   _TAG_TYPE_ tag_1, tag_2;
   _FLP_TYPE_ frc_1, frc_2;
   _SGN_TYPE_ nbr_1, nbr_2;
   _STR_TYPE_ str_1, str_2;
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   tag_1 = _ag_get_TAG_(val_1);
   tag_2 = _ag_get_TAG_(val_2);
   _stk_zap_CNT_();
   switch (tag_1)
     { case _NBR_TAG_: 
         { nbr_1 = _ag_get_NBR_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   if (nbr_op(nbr_1, nbr_2))
                     _stk_poke_EXP_(_TRUE_);
                   else 
                     _stk_poke_EXP_(_FALSE_);
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (frc_op(nbr_1, *frc_2))
                     _stk_poke_EXP_(_TRUE_);
                   else 
                     _stk_poke_EXP_(_FALSE_);
                   return; }}
           break; }
       case _FRC_TAG_:
         { frc_1 = _ag_get_FRC_(val_1);
           switch (tag_2)
             { case _NBR_TAG_: 
                 { nbr_2 = _ag_get_NBR_(val_2);
                   if (frc_op(*frc_1, nbr_2))
                     _stk_poke_EXP_(_TRUE_);
                   else 
                     _stk_poke_EXP_(_FALSE_);
                   return; }
               case _FRC_TAG_: 
                 { frc_2 = _ag_get_FRC_(val_2);
                   if (frc_op(*frc_1, *frc_2))
                     _stk_poke_EXP_(_TRUE_);
                   else 
                     _stk_poke_EXP_(_FALSE_);
                   return; }}}
       case _TXT_TAG_:
         { str_1 = _ag_get_TXT_(val_1);
           if (tag_2 == _TXT_TAG_) 
             { str_2 = _ag_get_TXT_(val_2);
               if (str_op(str_1, str_2))
                 _stk_poke_EXP_(_TRUE_);
               else 
                 _stk_poke_EXP_(_FALSE_);
               return; }}}
   _error_str_(_ATC_ERROR_, str); }

/*------------------------------------------------------------------------*/
/*  LSS                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... LSS] -> [... ... ... LSB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ LSS(_NIL_TYPE_)
 { bin(LSB, lss_STR); }

/*------------------------------------------------------------------------*/
/*  LSB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... LSB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _SGN_TYPE_ less_nbr_op(const _SGN_TYPE_ nbr_1,
                              const _SGN_TYPE_ nbr_2)
 { return (nbr_1 < nbr_2); }

static _SGN_TYPE_ less_frc_op(const _FLO_TYPE_ frc_1,
                              const _FLO_TYPE_ frc_2)
 { return (frc_1+_FRC_MIN_ < frc_2); }

static _SGN_TYPE_ less_txt_op(const _STR_TYPE_ str_1,
                              const _STR_TYPE_ str_2)
 { return (strcmp(str_1, str_2) < 0); }

static _NIL_TYPE_ LSB(_NIL_TYPE_)
 { compare(less_nbr_op, less_frc_op, less_txt_op, lss_STR); }

/*------------------------------------------------------------------------*/
/*  EQL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... EQL] -> [... ... ... EQB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EQL(_NIL_TYPE_)
 { bin(EQB, eql_STR); }
  
/*------------------------------------------------------------------------*/
/*  EQB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... EQB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _SGN_TYPE_ equal_nbr_op(const _SGN_TYPE_ nbr_1,
                               const _SGN_TYPE_ nbr_2)
 { return (nbr_1 == nbr_2); }

static _SGN_TYPE_ equal_frc_op(const _FLO_TYPE_ frc_1,
                               const _FLO_TYPE_ frc_2)
 { return (fabs(frc_1 - frc_2) < _FRC_MIN_); }

static _SGN_TYPE_ equal_txt_op(const _STR_TYPE_ str_1,
                               const _STR_TYPE_ str_2)
 { return (strcmp(str_1, str_2) == 0); }

static _NIL_TYPE_ EQB(_NIL_TYPE_)
 { compare(equal_nbr_op, equal_frc_op, equal_txt_op, eql_STR); }

/*------------------------------------------------------------------------*/
/*  GRT                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... GRT] -> [... ... ... GRB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ GRT(_NIL_TYPE_)
 { bin(GRB, grt_STR); }

/*------------------------------------------------------------------------*/
/*  GRB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... GRB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _SGN_TYPE_ greater_nbr_op(const _SGN_TYPE_ nbr_1, 
                                 const _SGN_TYPE_ nbr_2)
 { return (nbr_1 > nbr_2); }

static _SGN_TYPE_ greater_frc_op(const _FLO_TYPE_ frc_1, 
                                 const _FLO_TYPE_ frc_2)
 { return (frc_1-_FRC_MIN_ > frc_2); }

static _SGN_TYPE_ greater_txt_op(const _STR_TYPE_ str_1, 
                                 const _STR_TYPE_ str_2)
 { return (strcmp(str_1, str_2) > 0); }

static _NIL_TYPE_ GRB(_NIL_TYPE_)
 { compare(greater_nbr_op, greater_frc_op, greater_txt_op, grt_STR); }

/*------------------------------------------------------------------------*/
/*  EQV                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... EQV] -> [... ... ... EVB swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EQV(_NIL_TYPE_)
 { bin(EVB, eqv_STR); }
  
/*------------------------------------------------------------------------*/
/*  EVB                                                                   */
/*     expr-stack: [... ... ... ... VAL VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... EVB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EVB(_NIL_TYPE_)
 { _EXP_TYPE_ val_1, val_2;
   _stk_pop_EXP_(val_2);
   _stk_peek_EXP_(val_1);
   _stk_zap_CNT_();
   if(_mem_is_same_(val_1, val_2))
     _stk_poke_EXP_(_TRUE_); 
   else
     _stk_poke_EXP_(_FALSE_); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*-----------------C O N V E R S I O N     O P E R A T O R S--------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  TRN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TRN] -> [... ... ... ... TRU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TRN(_NIL_TYPE_)
 { una(TRU, trn_STR); }

/*------------------------------------------------------------------------*/
/*  TRU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... TRU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TRU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { return; }
       case _FRC_TAG_:
         { _FLP_TYPE_ frc = _ag_get_FRC_(val);
           _SGN_TYPE_ res = (_SGN_TYPE_)*frc;
           if (labs(res) > _NBR_MAX_)
             _error_str_(_NBR_ERROR_, trn_STR);
           _stk_poke_EXP_(_ag_make_NBR_(res));     
           return; }}
   _error_str_(_ATC_ERROR_, trn_STR); }
   
/*------------------------------------------------------------------------*/
/*  ABS                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ABS] -> [... ... ... ... ABU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ABS(_NIL_TYPE_)
 { una(ABU, abs_STR); }
  
/*------------------------------------------------------------------------*/
/*  ABU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ABU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ABU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _mem_claim_();
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           _stk_poke_EXP_(_ag_make_NBR_(labs(nbr)));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = fabs(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, abs_STR); }
   
/*------------------------------------------------------------------------*/
/*  CHR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... CHR] -> [... ... ... ... CHU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CHR(_NIL_TYPE_)
 { una(CHU, chr_STR); }

/*------------------------------------------------------------------------*/
/*  CHU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... CHU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CHU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   if (tag == _NBR_TAG_)
     { nbr = _ag_get_NBR_(val);
       if ((nbr >= 0) && (nbr <= 255))
         { _TEXT_BUF_[0] = (_CHA_TYPE_)nbr;
           _TEXT_BUF_[1] = 0;
           _mem_claim_STR_(_TEXT_BUF_);
           _stk_poke_EXP_(_ag_make_TXT_(_TEXT_BUF_));    
           return; }
       _error_str_(_RNG_ERROR_, chr_STR); }
   _error_str_(_ATC_ERROR_, chr_STR); }
   
/*------------------------------------------------------------------------*/
/*  ORD                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ORD] -> [... ... ... ... ORU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ORD(_NIL_TYPE_)
 { una(ORU, ord_STR); }

/*------------------------------------------------------------------------*/
/*  ORU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ORU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ORU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _STR_TYPE_ str;
   _CHA_TYPE_ ord;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   if (tag == _TXT_TAG_)
     { str = _ag_get_TXT_(val);
       if (strlen(str) == 1)
         { ord = str[0];
           _stk_poke_EXP_(_ag_make_NBR_(ord));     
           return; }
       _error_str_(_RNG_ERROR_, ord_STR); }
   _error_str_(_ATC_ERROR_, ord_STR); }
   
/*------------------------------------------------------------------------*/
/*  RND                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... RND] -> [... ... ... ... ... NBR] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ RND(_NIL_TYPE_)
 { _EXP_TYPE_ arg, nbr;
   _UNS_TYPE_ siz;
   _SGN_TYPE_ rnd;
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 0)
    { rnd = rand();
      nbr = _ag_make_NBR_(rnd);    
      _stk_poke_EXP_(nbr);
      _stk_zap_CNT_(); }
   else
     _error_str_(_NMA_ERROR_, rnd_STR); }

/*------------------------------------------------------------------------*/
/*  NUM                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... NUM] -> [... ... ... ... NMU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NUM(_NIL_TYPE_)
 { una(NMU, num_STR); }

/*------------------------------------------------------------------------*/
/*  NMU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... NMU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NMU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ frc;
   _SGN_TYPE_ res;
   _STR_TYPE_ str, end;
   _mem_claim_();
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
    _stk_zap_CNT_();
   if (tag == _TXT_TAG_)
     { str = _ag_get_TXT_(val);
       res = strtol(str, &end, 10);
       if (strlen(end))
         { frc = strtod(str, &end) ;
           if (strlen(end))
             val = _VOID_;
           else
             val = _ag_make_FRC_(&frc); }  
       else
         { if (labs(res) > _NBR_MAX_)
             _error_str_(_NBR_ERROR_, num_STR);
           val = _ag_make_NBR_(res); }    
       _stk_poke_EXP_(val); 
       return; }
   _error_str_(_ATC_ERROR_, num_STR); }
   
/*------------------------------------------------------------------------*/
/*  TEX                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TEX] -> [... ... ... ... TEU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TEX(_NIL_TYPE_)
 { una(TEU, tex_STR); }

/*------------------------------------------------------------------------*/
/*  TEU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... TEU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TEU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ n;
   _FLP_TYPE_ f;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_: 
         n = _ag_get_NBR_(val);
         sprintf(_TEXT_BUF_, "%d", n);
         _mem_claim_STR_(_TEXT_BUF_);
         val = _ag_make_TXT_(_TEXT_BUF_);    
         break;
       case _FRC_TAG_: 
         f = _ag_get_FRC_(val);
         sprintf(_TEXT_BUF_, "%g", *f);
         _mem_claim_STR_(_TEXT_BUF_);
         val = _ag_make_TXT_(_TEXT_BUF_);    
         break;
       case _TXT_TAG_: 
         break;
       default:
         val = _VOID_; }
   _stk_poke_EXP_(val); }
   
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*-------------T R A N S C E N D E N T A L     O P E R A T O R S----------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  SQT                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... SQT] -> [... ... ... ... SQU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SQT(_NIL_TYPE_)
 { una(SQU, sqt_STR); }

/*------------------------------------------------------------------------*/
/*  SQU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... SQU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SQU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _mem_claim_();
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           if (nbr < 0)
             _error_str_(_NEG_ERROR_, sqt_STR);
           flo = sqrt(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           if (*frc < 0)
             _error_str_(_NEG_ERROR_, sqt_STR);
           flo = sqrt(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, sqt_STR); }
   
/*------------------------------------------------------------------------*/
/*  SIN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... SIN] -> [... ... ... ... SNU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SIN(_NIL_TYPE_)
 { una(SNU, sin_STR); }

/*------------------------------------------------------------------------*/
/*  SNU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... SNU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SNU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ nbr;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _mem_claim_();
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           flo = sin(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = sin(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, sin_STR); }
   
/*------------------------------------------------------------------------*/
/*  COS                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... COS] -> [... ... ... ... CSU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ COS(_NIL_TYPE_)
 { una(CSU, cos_STR); }

/*------------------------------------------------------------------------*/
/*  CSU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... CSU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CSU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ nbr;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           flo = cos(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = cos(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, cos_STR); }
   
/*------------------------------------------------------------------------*/
/*  TAN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TAN] -> [... ... ... ... TNU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TAN(_NIL_TYPE_)
 { una(TNU, tan_STR); }

/*------------------------------------------------------------------------*/
/*  TNU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... TNU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TNU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ nbr;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           flo = tan(nbr);
           if (fabs(flo) >= _FRC_MAX_)
             _error_str_(_INF_ERROR_, tan_STR);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = tan(*frc);
           if (fabs(flo) >= _FRC_MAX_)
             _error_str_(_INF_ERROR_, tan_STR);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, tan_STR); }
 
/*------------------------------------------------------------------------*/
/*  ASN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ASN] -> [... ... ... ... ASU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ASN(_NIL_TYPE_)
 { una(ASU, asn_STR); }

/*------------------------------------------------------------------------*/
/*  ASU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ASU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ASU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           if ((nbr < -1) | (nbr > +1))
             _error_str_(_RNG_ERROR_, asn_STR);
           flo = asin(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           if ((*frc < -1) | (*frc > +1))
             _error_str_(_RNG_ERROR_, asn_STR);
           flo = asin(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, asn_STR); }
   
/*------------------------------------------------------------------------*/
/*  ACS                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ACS] -> [... ... ... ... ACU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ACS(_NIL_TYPE_)
 { una(ACU, acs_STR); }

/*------------------------------------------------------------------------*/
/*  CSU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... CSU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ACU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           if ((nbr < -1) | (nbr > +1))
             _error_str_(_RNG_ERROR_, acs_STR);
           flo = acos(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           if ((*frc < -1) | (*frc > +1))
             _error_str_(_RNG_ERROR_, acs_STR);
           flo = acos(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, acs_STR); }
   
/*------------------------------------------------------------------------*/
/*  ATN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ATN] -> [... ... ... ... ATU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ATN(_NIL_TYPE_)
 { una(ATU, atn_STR); }

/*------------------------------------------------------------------------*/
/*  ATU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... ATU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ATU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           flo = atan(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = atan(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, atn_STR); }
   
/*------------------------------------------------------------------------*/
/*  EPW                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... EPW] -> [... ... ... ... EPU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EPW(_NIL_TYPE_)
 { una(EPU, epw_STR); }

/*------------------------------------------------------------------------*/
/*  EPU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... EPU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EPU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           flo = exp(nbr);
           if (fabs(flo) >= _FRC_MAX_)
             _error_str_(_INF_ERROR_, epw_STR);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           flo = exp(*frc);
           if (fabs(flo) >= _FRC_MAX_)
             _error_str_(_INF_ERROR_, epw_STR);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, epw_STR); }
   
/*------------------------------------------------------------------------*/
/*  LOG                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... LOG] -> [... ... ... ... LGU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ LOG(_NIL_TYPE_)
 { una(LGU, log_STR); }

/*------------------------------------------------------------------------*/
/*  LGU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... LGU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ LGU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _FLO_TYPE_ flo;
   _FLP_TYPE_ frc;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _NBR_TAG_:
         { nbr = _ag_get_NBR_(val);
           if (nbr <= 0)
             _error_str_(_NEG_ERROR_, log_STR);
           flo = log(nbr);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }
       case _FRC_TAG_:
         { frc = _ag_get_FRC_(val);
           if (*frc <= 0)
             _error_str_(_NEG_ERROR_, log_STR);
           flo = log(*frc);
           _stk_poke_EXP_(_ag_make_FRC_(&flo));    
           return; }}
   _error_str_(_ATC_ERROR_, log_STR); }
   
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*----------------------S T R I N G     O P E R A T O R S-----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  EPL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... EPL] -> [... ... ... ... EPZ EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EPL(_NIL_TYPE_)
 { una(EPZ, epl_STR); }
 
/*------------------------------------------------------------------------*/
/*  EPZ                                                                   */
/*     expr-stack: [... ... ... ... ... STR] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... EPZ] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EPZ(_NIL_TYPE_)
 { _EXP_TYPE_ tab, val;
   _TAG_TYPE_ tag;
   _STR_TYPE_ str;
   _UNS_TYPE_ len;
   _stk_peek_EXP_(val);       
   tag = _ag_get_TAG_(val);
   if (tag == _TXT_TAG_)
     { str = _ag_get_TXT_(val);
       len = strlen(str);
       _mem_claim_SIZ_(3*len);
       _stk_peek_EXP_(val);       
       tab = _ag_make_TAB_(len);    
       _stk_poke_EXP_(tab);
       str = _ag_get_TXT_(val);
       while (len)
         { _TEXT_BUF_[0] = str[len-1];
           _TEXT_BUF_[1] = 0;
           _stk_peek_EXP_(tab);
           _ag_set_TAB_EXP_(tab, len--, _ag_make_TXT_(_TEXT_BUF_)); }    
       _stk_zap_CNT_();
       return; }
   _error_str_(_ATC_ERROR_, epl_STR); }

/*------------------------------------------------------------------------*/
/*  IPL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... IPL] -> [... ... ... ... IPZ EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IPL(_NIL_TYPE_)
 { una(IPZ, ipl_STR); }
 
/*------------------------------------------------------------------------*/
/*  IPZ                                                                   */
/*     expr-stack: [... ... ... ... ... TAB] -> [... ... ... ... ... STR] */
/*     cont-stack: [... ... ... ... ... IPZ] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IPZ(_NIL_TYPE_)
 { _EXP_TYPE_ elt, val;
   _TAG_TYPE_ tag;
   _UNS_TYPE_ len;
   _STR_TYPE_ chr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
    if (tag == _TAB_TAG_)
     { len = _ag_get_TAB_SIZ_(val);
       if (len > _BUF_SIZE_)
         _error_str_(_BUF_ERROR_, ipl_STR);
       _TEXT_BUF_[len] = 0;
       while (len)
         { elt = _ag_get_TAB_EXP_(val, len--);
           tag = _ag_get_TAG_(elt);
           if (tag != _TXT_TAG_)
             _error_str_(_ATC_ERROR_, ipl_STR);
           chr = _ag_get_TXT_(elt);
           if (strlen(chr) != 1)
             _error_str_(_ATC_ERROR_, ipl_STR);
           _TEXT_BUF_[len] = chr[0]; }
       _mem_claim_STR_(_TEXT_BUF_);
       val = _ag_make_TXT_(_TEXT_BUF_);    
       _stk_poke_EXP_(val);
       _stk_zap_CNT_();
       return; }
   _error_str_(_ATC_ERROR_, ipl_STR); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*--------------------I D E N T I T Y    O P E R A T O R S----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ nat_tag(const _TAG_TYPE_ tag)
 { _EXP_TYPE_ val;
   _stk_peek_EXP_(val);
   _stk_zap_CNT_();
   if (tag == _ag_get_TAG_(val))
     _stk_poke_EXP_(_TRUE_);
   else 
     _stk_poke_EXP_(_FALSE_); }
     
static _NIL_TYPE_ nat_2_tags(const _TAG_TYPE_ tag_1,
                             const _TAG_TYPE_ tag_2)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
    _stk_zap_CNT_();
   if ((tag == tag_1) || (tag == tag_2))
     _stk_poke_EXP_(_TRUE_);
   else 
     _stk_poke_EXP_(_FALSE_); }

/*------------------------------------------------------------------------*/
/*  NBR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... NBR] -> [... ... ... ... NBU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NBR(_NIL_TYPE_)
 { una(NBU, nbr_STR); }

/*------------------------------------------------------------------------*/
/*  NBU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... NBU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NBU(_NIL_TYPE_)
 { nat_tag(_NBR_TAG_); }
   
/*------------------------------------------------------------------------*/
/*  FRC                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... FRC] -> [... ... ... ... FRU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRC(_NIL_TYPE_)
 { una(FRU, frc_STR); }

/*------------------------------------------------------------------------*/
/*  FRU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... FRU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRU(_NIL_TYPE_)
 { nat_tag(_FRC_TAG_); }
   
/*------------------------------------------------------------------------*/
/*  TXT                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TXT] -> [... ... ... ... TXU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TXT(_NIL_TYPE_)
 { una(TXU, txt_STR); }

/*------------------------------------------------------------------------*/
/*  TXU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... TXU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TXU(_NIL_TYPE_)
 { nat_tag(_TXT_TAG_); }
   
/*------------------------------------------------------------------------*/
/*  FUN                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... FUN] -> [... ... ... ... FNU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FUN(_NIL_TYPE_)
 { una(FNU, fun_STR); }

/*------------------------------------------------------------------------*/
/*  FNU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... FNU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FNU(_NIL_TYPE_)
 { nat_2_tags(_FUN_TAG_, _NAT_TAG_); }
   
/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TBL] -> [... ... ... ... TBU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TBL(_NIL_TYPE_)
 { una(TBU, tbl_STR); }

/*------------------------------------------------------------------------*/
/*  TBU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... TBU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TBU(_NIL_TYPE_)
 { nat_tag(_TAB_TAG_); }

/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... VOI] -> [... ... ... ... VOU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ VDD(_NIL_TYPE_)
 { una(VDU, vdd_STR); }

/*------------------------------------------------------------------------*/
/*  TBU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... VDU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ VDU(_NIL_TYPE_)
 { nat_tag(_VOI_TAG_); }

/*------------------------------------------------------------------------*/
/*  TBL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... VOI] -> [... ... ... ... VOU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ PRO(_NIL_TYPE_)
 { una(PRO1, vdd_STR); }

/*------------------------------------------------------------------------*/
/*  TBU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... VDU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ PRO1(_NIL_TYPE_)
 { nat_tag(_PRO_TAG_); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------T A B L E     O P E R A T O R S-----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  SIZ                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... SIZ] -> [... ... ... ... SZU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SIZ(_NIL_TYPE_)
 { una(SZU, siz_STR); }

/*------------------------------------------------------------------------*/
/*  SZU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... SZU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ SZU(_NIL_TYPE_)
 { _EXP_TYPE_ val;
   _TAG_TYPE_ tag;
   _STR_TYPE_ str;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   switch (tag)
     { case _TAB_TAG_: 
         _stk_poke_EXP_(_ag_make_NBU_(_ag_get_TAB_SIZ_(val)));    
         return;
       case _TXT_TAG_:
         str = _ag_get_TXT_(val);
         _stk_poke_EXP_(_ag_make_NBU_(strlen(str))); 
         return; }   
   _error_str_(_ATC_ERROR_, siz_STR); }

/*------------------------------------------------------------------------*/
/*  TAB                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ARG TAB NBR EVL] */
/*     cont-stack: [... ... ... ... ... TAB] -> [... ... ... ... TBX EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EMP] */
/*     cont-stack: [... ... ... ... ... TAB] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TAB(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, tab;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 0)
     { _stk_poke_EXP_(_EMPTY_);
       _stk_zap_CNT_();
       return; }
   _mem_claim_SIZ_(siz);
   tab = _ag_make_TAB_(siz);    
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(tab);
   _stk_push_EXP_(_ONE_);
   exp = _ag_get_TAB_EXP_(arg, 1);
   _stk_push_EXP_(exp);
   _stk_poke_CNT_(TBX); 
   _stk_push_CNT_(EVL); }

/*------------------------------------------------------------------------*/
/*  TBX                                                                   */
/*     expr-stack: [... ... ARG TAB NBR VAL] -> [... ... ARG TAB NBR EVL] */
/*     cont-stack: [... ... ... ... ... TBX] -> [... ... ... ... TBX EVL] */
/*                                                                        */
/*     expr-stack: [... ... ARG TAB NBR VAL] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... TBX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TBX(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, nbr, tab, val;
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
     { _stk_push_EXP_(tab);
       _stk_push_EXP_(_ag_succ_NBR_(nbr));
       exp = _ag_get_TAB_EXP_(arg, ctr+1);
       _stk_push_EXP_(exp);
       _stk_push_CNT_(EVL); 
       return; }
   _stk_poke_EXP_(tab);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*----------------I N T E R A C T I O N    O P E R A T O R S--------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  DSP                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ARG -1- EVL] */
/*     cont-stack: [... ... ... ... ... DSP] -> [... ... ... ... DSX EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EOL] */
/*     cont-stack: [... ... ... ... ... DSP] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DSP(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 0)
     { _stk_poke_EXP_(_NULL_);
       _stk_zap_CNT_();
       return; }
   _stk_poke_EXP_(arg);
   _stk_push_EXP_(_ONE_);
   exp = _ag_get_TAB_EXP_(arg, 1);
   _stk_push_EXP_(exp);
   _stk_poke_CNT_(DSX); 
   _stk_push_CNT_(EVL); }

/*------------------------------------------------------------------------*/
/*  DSX                                                                   */
/*     expr-stack: [... ... ... ARG NBR VAL] -> [... ... ARG NBR EVL VAL] */
/*     cont-stack: [... ... ... ... ... DSX] -> [... ... ... DSX EVL DSY] */
/*                                                                        */
/*     expr-stack: [... ... ... ARG NBR VAL] -> [... ... ... ... EOL VAL] */
/*     cont-stack: [... ... ... ... ... DSX] -> [... ... ... ... ... DSY] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DSX(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, nbr, val;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_pop_EXP_(nbr);
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   if (ctr < siz)
     { _stk_push_EXP_(_ag_succ_NBR_(nbr));
       exp = _ag_get_TAB_EXP_(arg, ctr+1);
       _stk_push_EXP_(exp); 
       _stk_push_EXP_(val); 
       _stk_push_CNT_(EVL);
       _stk_push_CNT_(DSY);
       return; }
   _stk_poke_EXP_(_NULL_);
   _stk_push_EXP_(val);
   _stk_poke_CNT_(DSY); }
       
/*------------------------------------------------------------------------*/
/*  DSY                                                                   */
/*     expr-stack: [... ... ... ... ... EVL] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... DSY] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... EVL] -> [... ... ... TAB NBR EVL] */
/*     cont-stack: [... ... ... ... ... DSY] -> [... ... ... ... DSZ DSY] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DSY(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nam;
   _SGN_TYPE_ nbr;
   _FLP_TYPE_ frc;
   _STR_TYPE_ str;
   _UNS_TYPE_ siz;
   _TAG_TYPE_ tag;
   _stk_claim_();
   _stk_zap_CNT_();
   _stk_pop_EXP_(exp);
   tag = _ag_get_TAG_(exp);
   switch (tag)
     { case _FRC_TAG_:
         frc = _ag_get_FRC_(exp);
         sprintf(_TEXT_BUF_, "%g", *frc);
         break;
       case _FUN_TAG_:
         nam = _ag_get_FUN_NAM_(exp);
         str = _ag_get_TXT_(nam);
          sprintf(_TEXT_BUF_, "<function  %s>", str);
         break;
       case _NAT_TAG_:
         nam = _ag_get_NAT_NAM_(exp);
         str = _ag_get_TXT_(nam);
         sprintf(_TEXT_BUF_, "<native function  %s>", str);
         break;
       case _NBR_TAG_:
         nbr = _ag_get_NBR_(exp);
         sprintf(_TEXT_BUF_, "%d", nbr);
         break;
       case _TXT_TAG_:
         str = _ag_get_TXT_(exp);
         sprintf(_TEXT_BUF_, "%s", str);
         break;
       case _TAB_TAG_:
         siz = _ag_get_TAB_SIZ_(exp);
         if (siz > 0)
           { _stk_push_EXP_(exp);
             exp = _ag_get_TAB_EXP_(exp, 1);
             _stk_push_EXP_(_ONE_);
             _stk_push_EXP_(exp);
             _stk_push_CNT_(DSZ);
             _stk_push_CNT_(DSY); 
             sprintf(_TEXT_BUF_, "["); }
         else
           sprintf(_TEXT_BUF_, "[]"); 
         break;
       case _VOI_TAG_:
         sprintf(_TEXT_BUF_, "<_NIL_TYPE_>");
         break;
       default:
         _error_str_(_ATC_ERROR_, dsp_STR); }
   _display_(_TEXT_BUF_); }
                               
/*------------------------------------------------------------------------*/
/*  DSZ                                                                   */
/*     expr-stack: [... ... ... ... TAB NBR] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... DSZ] -> [... ... ... ... ... ...] */
/*                                                                        */
/*     expr-stack: [... ... ... ... TAB NBR] -> [... ... ... TAB NBR EVL] */
/*     cont-stack: [... ... ... ... ... DSZ] -> [... ... ... ... DSZ DSY] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ DSZ(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr;
   _UNS_TYPE_ idx, siz;
   _stk_claim_();
   _stk_pop_EXP_(nbr);
   _stk_peek_EXP_(exp);
   idx = _ag_get_NBU_(nbr); 
   siz = _ag_get_TAB_SIZ_(exp);
   if (idx < siz)
     { sprintf(_TEXT_BUF_, ", ");
       _stk_push_EXP_(_ag_succ_NBR_(nbr));
       _stk_push_EXP_(_ag_get_TAB_EXP_(exp, idx+1)); 
       _stk_push_CNT_(DSY); }
   else
     { _stk_zap_EXP_();
       _stk_zap_CNT_();
       sprintf(_TEXT_BUF_, "]"); }
   _display_(_TEXT_BUF_); }
      
/*------------------------------------------------------------------------*/
/*  ACP                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... ACP] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ACP(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 0)
    { _stk_zap_EXP_();
      _stk_zap_CNT_();
      _accept_(); }
   _error_str_(_NMA_ERROR_, acp_STR); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*----------------------B O O L E A N    O P E R A T O R S----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  TRR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TRR] -> [... ... ... ... ... EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TRR(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(EVL); 
       return; }
   _error_str_(_NMA_ERROR_, trr_STR); }

/*------------------------------------------------------------------------*/
/*  FLS                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... FLS] -> [... ... ... ... ... EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FLS(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(_ag_get_TAB_EXP_(arg, 2));
       _stk_poke_CNT_(EVL); 
       return; }
   _error_str_(_NMA_ERROR_, fls_STR); }

/*------------------------------------------------------------------------*/
/*  AND                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... AND] -> [... ... ... ... ANC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ AND(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(_ag_get_TAB_EXP_(arg, 2));
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(ANC); 
       _stk_push_CNT_(EVL);
       return; }
  _error_str_(_NMA_ERROR_, and_STR); }

/*------------------------------------------------------------------------*/
/*  ANC                                                                   */
/*     expr-stack: [... ... ... ... EVL FUN] -> [... ... ... ... FUN TAB] */
/*     cont-stack: [... ... ... ... ... ANC] -> [... ... ... ... ... CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... EVL NAT] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ANC] -> [... ... ... ... ... EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... EVL NAT] -> [... ... ... ... ... ARG] */
/*     cont-stack: [... ... ... ... ... ANC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ANC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, fun;
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _stk_pop_EXP_(fun);
         _stk_peek_EXP_(exp);
         _stk_poke_EXP_(fun);
         _ag_set_TAB_EXP_(arg, 1, exp); 
         _ag_set_TAB_EXP_(arg, 2, _FALSE_);
         _stk_push_EXP_(arg);
         _stk_poke_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_(); 
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_poke_CNT_(EVL);
             return; }
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_poke_EXP_(_FALSE_);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, and_STR); }
   _error_str_(_IAG_ERROR_, and_STR); }

/*------------------------------------------------------------------------*/
/*  ORR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... ORR] -> [... ... ... ... ORC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ORR(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(_ag_get_TAB_EXP_(arg, 2));
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(ORC); 
       _stk_push_CNT_(EVL);
       return; }
  _error_str_(_NMA_ERROR_, orr_STR); }

/*------------------------------------------------------------------------*/
/*  ORC                                                                   */
/*     expr-stack: [... ... ... ... EVL FUN] -> [... ... ... ... FUN TAB] */
/*     cont-stack: [... ... ... ... ... ORC] -> [... ... ... ... ... CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... EVL NAT] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ORC] -> [... ... ... ... ... EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... EVL NAT] -> [... ... ... ... ... ARG] */
/*     cont-stack: [... ... ... ... ... ORC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ORC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, fun;
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _stk_pop_EXP_(fun);
         _stk_peek_EXP_(exp);
         _stk_poke_EXP_(fun);
         _ag_set_TAB_EXP_(arg, 1, _TRUE_); 
         _ag_set_TAB_EXP_(arg, 2, exp);
         _stk_push_EXP_(arg);
         _stk_poke_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_(); 
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_poke_CNT_(EVL);
             return; }
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_poke_EXP_(_TRUE_);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, orr_STR); }
   _error_str_(_IAG_ERROR_, orr_STR); }
   
/*------------------------------------------------------------------------*/
/*  NOT                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... NOT] -> [... ... ... ... NTC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NOT(_NIL_TYPE_)
 { una(NTC, not_STR); }

/*------------------------------------------------------------------------*/
/*  NTC                                                                   */
/*     expr-stack: [... ... ... ... ... FUN] -> [... ... ... ... FUN TAB] */
/*     cont-stack: [... ... ... ... ... NTC] -> [... ... ... ... ... CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... ARG] */
/*     cont-stack: [... ... ... ... ... NTC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ NTC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, fun;
   _stk_claim_();
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _ag_set_TAB_EXP_(arg, 1, _FALSE_); 
         _ag_set_TAB_EXP_(arg, 2, _TRUE_);
         _stk_push_EXP_(arg);
         _stk_poke_CNT_(CAL);
         return;
       case _NAT_TAG_:
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_poke_EXP_(_FALSE_);
             _stk_zap_CNT_(); 
             return; }
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_poke_EXP_(_TRUE_);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, not_STR); }
   _error_str_(_IAG_ERROR_, not_STR); }
   
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------S T R U C T U R E    O P E R A T O R S----------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  BEG                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ARG *1* EVL] */
/*     cont-stack: [... ... ... ... ... BEG] -> [... ... ... ... BXG EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... VOI] */
/*     cont-stack: [... ... ... ... ... BEG] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ BEG(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 0)
     { _stk_poke_EXP_(_VOID_);
       _stk_zap_CNT_();
       return; }
   _stk_poke_EXP_(arg);
   _stk_push_EXP_(_ONE_);
   exp = _ag_get_TAB_EXP_(arg, 1);
   _stk_push_EXP_(exp);
   _stk_poke_CNT_(BXG); 
   _stk_push_CNT_(EVL); }

/*------------------------------------------------------------------------*/
/*  BXG                                                                   */
/*     expr-stack: [... ... ... ARG NBR VAL] -> [... ... ... ARG NBR EVL] */
/*     cont-stack: [... ... ... ... ... BXG] -> [... ... ... ... BXG EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... ARG NBR VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... BXG] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ BXG(_NIL_TYPE_)
 { _EXP_TYPE_ arg, exp, nbr, val;
   _UNS_TYPE_ ctr, siz;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_pop_EXP_(nbr);
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   ctr = _ag_get_NBU_(nbr);
   if (ctr < siz)
     { _stk_push_EXP_(_ag_succ_NBR_(nbr));
       exp = _ag_get_TAB_EXP_(arg, ctr+1);
       _stk_push_EXP_(exp);
       _stk_push_CNT_(EVL); 
       return; }
   _stk_poke_EXP_(val);
   _stk_zap_CNT_(); }
       
/*------------------------------------------------------------------------*/
/*  CLL                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... DCT EVL] */
/*     cont-stack: [... ... ... ... ... CLL] -> [... ... ... ... CLX EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CLL(_NIL_TYPE_)
 { _EXP_TYPE_ arg, dct, env, exp;
   _UNS_TYPE_ siz;
   _stk_claim_();
   // _mem_claim_(); // dvd
   _mem_claim_SIZ_(_ag_get_TAB_SIZ_(_STK_)); // dvd: pulled up from _env_save_
   dct = _ag_make_DCT_();
   env = _ag_make_ENV_();
   _stk_pop_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 1)
     { _stk_zap_CNT_();
       _env_save_(env);
       _stk_push_EXP_(_DCT_);
       _ag_set_DCT_NAM_(dct, _CONT_);
		   _ag_set_DCT_VAL_(dct, env);
		   _ag_set_DCT_DCT_(dct, _DCT_);
		   _DCT_ = dct;
		   exp = _ag_get_TAB_EXP_(arg, 1);
       _stk_push_EXP_(exp);
       _stk_push_CNT_(CLX); 
       _stk_push_CNT_(EVL); }
  else
    _error_str_(_NMA_ERROR_, cll_STR); }
     
/*------------------------------------------------------------------------*/
/*  CLX                                                                   */
/*     expr-stack: [... ... ... ... DCT VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... CLX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CLX(_NIL_TYPE_)
  { _EXP_TYPE_ val;
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(_DCT_);
   _stk_poke_EXP_(val);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  CON                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... EVL EVL] */
/*     cont-stack: [... ... ... ... ... CON] -> [... ... ... COX swp EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ CON(_NIL_TYPE_)
 { bin(COX, con_STR); }

/*------------------------------------------------------------------------*/
/*  COX                                                                   */
/*     expr-stack: [... ... ... ... ENV VAL] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... COX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ COX(_NIL_TYPE_)
 { _EXP_TYPE_ env, val;
   _TAG_TYPE_ tag;
   _mem_claim_SIZ_(_ag_get_TAB_SIZ_(_STK_)); // dvd: pulled up from _env_load_
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(env);
   tag = _ag_get_TAG_(env);
   if (tag == _ENV_TAG_)
     { _env_load_(env);
       _stk_push_EXP_(val); }
   else
     _error_str_(_ATC_ERROR_, con_STR); }

/*------------------------------------------------------------------------*/
/*  IFF                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... TAB EVL] */
/*     cont-stack: [... ... ... ... ... IFF] -> [... ... ... ... IFC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IFF(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 3)
     { _stk_poke_EXP_(arg);
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(IFC); 
       _stk_push_CNT_(EVL); 
       return; }
  _error_str_(_NMA_ERROR_, iff_STR); }
  
/*------------------------------------------------------------------------*/
/*  IFC                                                                   */
/*     expr-stack: [... ... ... ... TAB FUN] -> [... ... ... ... FUN TAB] */
/*     cont-stack: [... ... ... ... ... IFC] -> [... ... ... ... ... CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... ... TAB NAT] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... IFC] -> [... ... ... ... ... EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ IFC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, fun, tab;
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _stk_pop_EXP_(fun);
         _stk_peek_EXP_(tab);
         _stk_poke_EXP_(fun);
         _ag_set_TAB_EXP_(arg, 1, _ag_get_TAB_EXP_(tab, 2)); 
         _ag_set_TAB_EXP_(arg, 2, _ag_get_TAB_EXP_(tab, 3));
         _stk_push_EXP_(arg);
         _stk_poke_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_();
         _stk_peek_EXP_(tab);
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_poke_EXP_(_ag_get_TAB_EXP_(tab, 2));
             _stk_poke_CNT_(EVL);
             return; }
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_poke_EXP_(_ag_get_TAB_EXP_(tab, 3));
             _stk_poke_CNT_(EVL);
             return; }
         _error_str_(_NAB_ERROR_, iff_STR); }
   _error_str_(_NAF_ERROR_, iff_STR); }

/*------------------------------------------------------------------------*/
/*  WHI                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... TAB VOI EVL] */
/*     cont-stack: [... ... ... ... ... WHI] -> [... ... ... ... WHC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ WHI(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(arg);
       _stk_push_EXP_(_VOID_);
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(WHC); 
       _stk_push_CNT_(EVL);
       return; }
  _error_str_(_NMA_ERROR_, whi_STR); }

/*------------------------------------------------------------------------*/
/*  WHC                                                                   */
/*     expr-stack: [... ... ... TAB VAL FUN] -> [... ... TAB VAL FUN TAB] */
/*     cont-stack: [... ... ... ... ... WHC] -> [... ... ... ... WHC CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL NAT] -> [... ... ... ... TAB EVL] */
/*     cont-stack: [... ... ... ... ... WHC] -> [... ... ... ... WHE EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL NAT] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... WHC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ WHC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, fun, tab, val;
   _stk_claim_();
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _ag_set_TAB_EXP_(arg, 1, _TRUE_); 
         _ag_set_TAB_EXP_(arg, 2, _FALSE_);
         _stk_push_EXP_(arg);
         _stk_push_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_(); 
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_zap_EXP_();
             _stk_peek_EXP_(tab);
             _stk_push_EXP_(_ag_get_TAB_EXP_(tab, 2));
             _stk_poke_CNT_(WHE); 
             _stk_push_CNT_(EVL);
             return; }
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_pop_EXP_(val);
             _stk_poke_EXP_(val);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, whi_STR); }
   _error_str_(_IAG_ERROR_, whi_STR); }
  
/*------------------------------------------------------------------------*/
/*  WHE                                                                   */
/*     expr-stack: [... ... ... ... TAB VAL] -> [... ... ... TAB VAL EVL] */
/*     cont-stack: [... ... ... ... ... WHE] -> [... ... ... ... WHC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ WHE(_NIL_TYPE_)
 { _EXP_TYPE_ arg, val;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(val);
   _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
   _stk_poke_CNT_(WHC); 
   _stk_push_CNT_(EVL); 
   _ESCAPE_; }

/*------------------------------------------------------------------------*/
/*  UNT                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... TAB EVL] */
/*     cont-stack: [... ... ... ... ... UNT] -> [... ... ... ... UNE EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ UNT(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 2)
     { _stk_poke_EXP_(arg);
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 2));
       _stk_poke_CNT_(UNE); 
       _stk_push_CNT_(EVL);
       return; }
  _error_str_(_NMA_ERROR_, unt_STR); }

/*------------------------------------------------------------------------*/
/*  UNE                                                                   */
/*     expr-stack: [... ... ... ... TAB VAL] -> [... ... ... TAB VAL EVL] */
/*     cont-stack: [... ... ... ... ... UNE] -> [... ... ... ... UNC EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ UNE(_NIL_TYPE_)
 { _EXP_TYPE_ arg, val;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(val);
   _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
   _stk_poke_CNT_(UNC); 
   _stk_push_CNT_(EVL); 
   _ESCAPE_; }

/*------------------------------------------------------------------------*/
/*  UNC                                                                   */
/*     expr-stack: [... ... ... TAB VAL FUN] -> [... ... TAB VAL FUN TAB] */
/*     cont-stack: [... ... ... ... ... UNC] -> [... ... ... ... UNC CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL NAT] -> [... ... ... ... TAB EVL] */
/*     cont-stack: [... ... ... ... ... UNC] -> [... ... ... ... UNE EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL NAT] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... UNC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ UNC(_NIL_TYPE_)
 { _EXP_TYPE_ arg, fun, tab, val;
   _stk_claim_();
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _ag_set_TAB_EXP_(arg, 1, _TRUE_); 
         _ag_set_TAB_EXP_(arg, 2, _FALSE_);
         _stk_push_EXP_(arg);
         _stk_push_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_(); 
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_zap_EXP_();
             _stk_peek_EXP_(tab);
             _stk_push_EXP_(_ag_get_TAB_EXP_(tab, 2));
             _stk_poke_CNT_(UNE); 
             _stk_push_CNT_(EVL);
       return; }
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_pop_EXP_(val);
             _stk_poke_EXP_(val);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, unt_STR); }
   _error_str_(_IAG_ERROR_, unt_STR); }
  
/*------------------------------------------------------------------------*/
/*  FOR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ARG EVL] */
/*     cont-stack: [... ... ... ... ... FOR] -> [... ... ... ... FRS EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FOR(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_claim_();
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 4)
     { _stk_poke_EXP_(arg);
       _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 1));
       _stk_poke_CNT_(FRS); 
       _stk_push_CNT_(EVL);
       return; }
  _error_str_(_NMA_ERROR_, for_STR); }

/*------------------------------------------------------------------------*/
/*  FRS                                                                   */
/*     expr-stack: [... ... ... ... ARG VAL] -> [... ... ... ARG VOI EVL] */
/*     cont-stack: [... ... ... ... ... FRS] -> [... ... ... ... FRX EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRS(_NIL_TYPE_)
 { _EXP_TYPE_ arg, val;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(_VOID_);
   _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 3));
   _stk_poke_CNT_(FRX); 
   _stk_push_CNT_(EVL);
   return; }
   
/*------------------------------------------------------------------------*/
/*  FRX                                                                   */
/*     expr-stack: [... ... ... TAB VAL FUN] -> [... ... TAB VAL FUN TAB] */
/*     cont-stack: [... ... ... ... ... FRX] -> [... ... ... ... FRX CAL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL FUN] -> [... ... ... ... TAB EVL] */
/*     cont-stack: [... ... ... ... ... FRX] -> [... ... ... ... FRE EVL] */
/*                                                                        */
/*     expr-stack: [... ... ... TAB VAL FUN] -> [... ... ... ... ... VAL] */
/*     cont-stack: [... ... ... ... ... FRX] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRX(_NIL_TYPE_)
 { _EXP_TYPE_ arg, fun, tab, val;
   _stk_claim_();
   _mem_claim_();
   _stk_peek_EXP_(fun);
   switch (_ag_get_TAG_(fun))
     { case _FUN_TAG_:
         arg = _ag_make_TAB_(2);    
         _ag_set_TAB_EXP_(arg, 1, _TRUE_); 
         _ag_set_TAB_EXP_(arg, 2, _FALSE_);
         _stk_push_EXP_(arg);
         _stk_push_CNT_(CAL);
         return;
       case _NAT_TAG_:
         _stk_zap_EXP_(); 
         if (_mem_is_same_(fun, _TRUE_))
           { _stk_zap_EXP_();
             _stk_peek_EXP_(tab);
             _stk_push_EXP_(_ag_get_TAB_EXP_(tab, 4));
             _stk_poke_CNT_(FRE); 
             _stk_push_CNT_(EVL);
             return; }
         if (_mem_is_same_(fun, _FALSE_))
           { _stk_pop_EXP_(val);
             _stk_poke_EXP_(val);
             _stk_zap_CNT_(); 
             return; }
         _error_str_(_NAB_ERROR_, for_STR); }
   _error_str_(_IAG_ERROR_, for_STR); }
  
/*------------------------------------------------------------------------*/
/*  FRE                                                                   */
/*     expr-stack: [... ... ... ... ARG VAL] -> [... ... ... ARG VAL EVL] */
/*     cont-stack: [... ... ... ... ... FRE] -> [... ... ... ... FRI EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRE(_NIL_TYPE_)
 { _EXP_TYPE_ arg, val;
   _stk_claim_();
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(val);
   _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 2));
   _stk_poke_CNT_(FRI); 
   _stk_push_CNT_(EVL); 
   _ESCAPE_; }
   
/*------------------------------------------------------------------------*/
/*  FRI                                                                   */
/*     expr-stack: [... ... ... ARG VAL VAL] -> [... ... ... ARG VAL EVL] */
/*     cont-stack: [... ... ... ... ... FRI] -> [... ... ... ... FRX EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ FRI(_NIL_TYPE_)
 {  _EXP_TYPE_ arg, val;
   _stk_claim_();
   _stk_zap_EXP_();
   _stk_pop_EXP_(val);
   _stk_peek_EXP_(arg);
   _stk_push_EXP_(val);
   _stk_push_EXP_(_ag_get_TAB_EXP_(arg, 3));
   _stk_poke_CNT_(FRX); 
   _stk_push_CNT_(EVL); }   

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*---------------------M E T A     O P E R A T O R S----------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  LOD                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EXP] */
/*     cont-stack: [... ... ... ... ... LOD] -> [... ... ... ... LOX EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ LOD(_NIL_TYPE_)
 { una(LOU, lod_STR); }
   
/*------------------------------------------------------------------------*/
/*  LOU                                                                   */
/*     expr-stack: [... ... ... ... ... TXT] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... LOU] -> [... ... ... PRI EVL RDD] */
/*------------------------------------------------------------------------*/

 static _NIL_TYPE_ LOU(_NIL_TYPE_)
 { _EXP_TYPE_ txt;
   _TAG_TYPE_ tag;
   _STR_TYPE_ str;
   _stk_pop_EXP_(txt);
   tag = _ag_get_TAG_(txt);
   _stk_zap_CNT_();
   if (tag == _TXT_TAG_)
    { str = _ag_get_TXT_(txt);
      sprintf(_TEXT_BUF_, "%s", str);
      _load_(_TEXT_BUF_); }
   _error_str_(_ATC_ERROR_, lod_STR); }

/*------------------------------------------------------------------------*/
/*  REA                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... REA] -> [... ... ... ... REU EVL] */
/*------------------------------------------------------------------------*/

static _STR_TYPE_ REA_buf = 0;

static _NIL_TYPE_ REA(_NIL_TYPE_)
 { una(REU, rea_STR); }

/*------------------------------------------------------------------------*/
/*  REU                                                                   */
/*     expr-stack: [... ... ... ... ... TXT] -> [... ... ... ... TXT *T*] */
/*     cont-stack: [... ... ... ... ... REU] -> [... ... ... ... ... rea] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ REU(_NIL_TYPE_)
 { _EXP_TYPE_ txt;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(txt);
   tag = _ag_get_TAG_(txt);
   if (tag == _TXT_TAG_)
     { _stk_push_EXP_(_TRUE_);
       _stk_poke_CNT_(RDD);
       return; }
   _error_str_(_ATC_ERROR_, rea_STR); }

/*------------------------------------------------------------------------*/
/*  EVA                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... EVA] -> [... ... ... ... EVU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EVA(_NIL_TYPE_)
 { una(EVU, eva_STR); }

/*------------------------------------------------------------------------*/
/*  EVU                                                                   */
/*     expr-stack: [... ... ... ... ... AGR] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... EVU] -> [... ... ... ... ... EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ EVU(_NIL_TYPE_)
 { _stk_poke_CNT_(EVL); }

/*------------------------------------------------------------------------*/
/*  PRI                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... PRI] -> [... ... ... ... PRU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ PRI(_NIL_TYPE_)
 { una(PRU, pri_STR); }

/*------------------------------------------------------------------------*/
/*  PRU                                                                   */
/*     expr-stack: [... ... ... ... ... EVL] -> [... ... ... ... ... VOI] */
/*     cont-stack: [... ... ... ... ... PRU] -> [... ... ... ... ... pri] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ PRU(_NIL_TYPE_)
 { _stk_poke_CNT_(PRT); }

/*------------------------------------------------------------------------*/
/*  TAG                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... TAG] -> [... ... ... ... TAU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TAG(_NIL_TYPE_)
 { una(TAU, tag_STR); }
 
/*------------------------------------------------------------------------*/
/*  TAU                                                                   */
/*     expr-stack: [... ... ... ... ... EVL] -> [... ... ... ... ... NBR] */
/*     cont-stack: [... ... ... ... ... TAU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ TAU(_NIL_TYPE_)
 { _EXP_TYPE_ exp, nbr;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(exp);
   tag = _ag_get_TAG_(exp);
   nbr = _ag_make_NBR_(tag);    
   _stk_poke_EXP_(nbr);
   _stk_zap_CNT_(); }

/*------------------------------------------------------------------------*/
/*  MAK                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... MAK] -> [... ... ... ... MKU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ MAK(_NIL_TYPE_)
 { una(MKU, mak_STR); }

/*------------------------------------------------------------------------*/
/*  MKU                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... MKU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ MKU(_NIL_TYPE_)
 { _EXP_TYPE_ exp, val;
   _TAG_TYPE_ tag;
   _SGN_TYPE_ nbr;
   _stk_peek_EXP_(val);
   tag = _ag_get_TAG_(val);
   _stk_zap_CNT_();
   if (tag != _NBR_TAG_)
     _error_str_(_ATC_ERROR_, mak_STR);
   nbr = _ag_get_NBR_(val);
   if ((nbr < 0) || (nbr > 17))
     _error_str_(_RNG_ERROR_, mak_STR);
   switch (nbr)
     { case _VOI_TAG_:
         exp = _VOID_;    
         break;
       case _NAT_TAG_:
         exp = _ag_make_NAT_();    
         break;
       case _FUN_TAG_:
         exp = _ag_make_FUN_();    
         break;
       case _VAR_TAG_:
         exp = _ag_make_VAR_();    
         break;
       case _APL_TAG_:
         exp = _ag_make_APL_();    
         break;
       case _TBL_TAG_:
         exp = _ag_make_TBL_();    
         break;
       case _DEF_TAG_:
         exp = _ag_make_DEF_();    
         break;
       case _SET_TAG_:
         exp = _ag_make_SET_();    
         break;
       case _DCT_TAG_:
         exp = _ag_make_DCT_();    
         break;
       case _ENV_TAG_:
         exp = _ag_make_ENV_();    
         break;
       default:
         exp = _VOID_;    
         _error_str_(_TAG_ERROR_, mak_STR); }
   _stk_poke_EXP_(exp); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*----------------------------I N T E R R U P T --------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*  ign                                                                   */
/*     expr-stack: [... ... ... ... ... VAL] -> [... ... ... ... ... ...] */
/*     cont-stack: [... ... ... ... ... ign] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ign(_NIL_TYPE_)
 { _stk_zap_EXP_();
   _stk_zap_CNT_(); }
   
/*------------------------------------------------------------------------*/
/*  ESC                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... VOI] */
/*     cont-stack: [... ... ... ... ... ESC] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ESC(_NIL_TYPE_)
 { _EXP_TYPE_ arg;
   _UNS_TYPE_ siz;
   _stk_peek_EXP_(arg);
   siz = _ag_get_TAB_SIZ_(arg);
   if (siz == 1)
		 { _ESC_ = _ag_get_TAB_EXP_(arg, 1);
		   _stk_poke_EXP_(_VOID_);
		   _stk_zap_CNT_(); }
	 else
     _error_str_(_NMA_ERROR_, esc_STR); }
   
/*------------------------------------------------------------------------*/
/*  ERR                                                                   */
/*     expr-stack: [... ... ... ... ... ARG] -> [... ... ... ... ... EVL] */
/*     cont-stack: [... ... ... ... ... ERR] -> [... ... ... ... ERU EVL] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ERR(_NIL_TYPE_)
 { una(ERU, err_STR); }

/*------------------------------------------------------------------------*/
/*  ERU                                                                   */
/*     expr-stack: [... ... ... ... ... TXT] -> [... ... ... ... ... VOI] */
/*     cont-stack: [... ... ... ... ... ERU] -> [... ... ... ... ... ...] */
/*------------------------------------------------------------------------*/

static _NIL_TYPE_ ERU(_NIL_TYPE_)
 { _EXP_TYPE_ txt;
   _TAG_TYPE_ tag;
   _stk_peek_EXP_(txt);
   tag = _ag_get_TAG_(txt);
   if (tag == _TXT_TAG_)
     { _error_msg_(_USR_ERROR_, txt); 
       return; }
   _error_str_(_ATC_ERROR_, err_STR); }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

static _EXP_TYPE_ install_var(const _STR_TYPE_ str,
                              const _EXP_TYPE_ exp,
                              const _EXP_TYPE_ dct)
 { _EXP_TYPE_ nam = _env_make_NAM_(str);    
   _EXP_TYPE_ dcx = _ag_make_DCT_();    
   _ag_set_DCT_NAM_(dcx, nam);
   _ag_set_DCT_VAL_(dcx, exp);
   _ag_set_DCT_DCT_(dcx, dct);
   return dcx; }
   
static _EXP_TYPE_ install_fun(const _STR_TYPE_ str,
                              const _UNS_TYPE_ nat,
                              const _EXP_TYPE_ dct)
 { _EXP_TYPE_ dcx, exp, nam, nbr;
   exp = _ag_make_NAT_();    
   nam = _env_make_NAM_(str);    
   dcx = _ag_make_DCT_();    
   nbr = _ag_make_NBU_(nat);     
   _ag_set_NAT_NAM_(exp, nam);
   _ag_set_NAT_NBR_(exp, nbr);
   _ag_set_DCT_NAM_(dcx, nam);
   _ag_set_DCT_VAL_(dcx, exp);
   _ag_set_DCT_DCT_(dcx, dct);
   return dcx; }
   
static _EXP_TYPE_ lookup(const _STR_TYPE_ str,
                         const _EXP_TYPE_ DCT)
 { _EXP_TYPE_ nam, dct;
   nam = _env_make_NAM_(str);    
   _dct_locate_(nam, dct, DCT);
   return _ag_get_DCT_VAL_(dct); }

/* public functions */

/*------------------------------------------------------------------------*/
/*  NAT                                                                   */
/*     expr-stack: [... ... ... ... NBR TAB] -> [... ... ... ... ... TAB] */
/*     cont-stack: [... ... ... ... ... NAT] -> [... ... ... ... ... ***] */
/*------------------------------------------------------------------------*/

_NIL_TYPE_ _eval_NAT_(_NIL_TYPE_)
 { _EXP_TYPE_ nbr, tab;
   _SGN_TYPE_ nat;
   _TAG_TYPE_ tag;
   _stk_pop_EXP_(tab);
   _stk_peek_EXP_(nbr);
   _stk_poke_EXP_(tab);
   tag = _ag_get_TAG_(tab);
   nat = _ag_get_NBR_(nbr);
   if (tag != _TAB_TAG_)
     _error_str_(_IAG_ERROR_, STR_tab[nat]);
   _stk_poke_CNT_(FUN_tab[nat]); }
   
_NIL_TYPE_ _nat_reset_(_NIL_TYPE_)
 { _EOLN_  = _env_make_NAM_(nwl_STR);    
   _NULL_  = _env_make_NAM_(nul_STR);    
   _TAB_   = _env_make_NAM_(tab_STR);     
   _BEGIN_ = _env_make_NAM_(beg_STR);      
   _CONT_  = _env_make_NAM_(cnt_STR); }  
   
_NIL_TYPE_ _nat_interrupt_(_NIL_TYPE_)
 { _stk_claim_();
   _stk_push_EXP_(_ESC_);
   _stk_push_CNT_(ign);
   _stk_push_CNT_(EVL); }
   
_EXP_TYPE_ _nat_install_(_NIL_TYPE_)
 { _EXP_TYPE_ dct;
   _UNS_TYPE_ ctr;
   _VOID_  = _ag_make_VOI_();    
   _EOLN_  = _env_make_NAM_(nwl_STR);    
   _NULL_  = _env_make_NAM_(nul_STR);    
   dct = install_var(eol_STR, _EOLN_, _VOID_);
   dct = install_var(voi_STR, _VOID_, dct);
   for (ctr = 0; ctr < NATIVE_SIZE; ctr++)
     dct = install_fun(STR_tab[ctr], ctr, dct);
   _TRUE_  = lookup(trr_STR, dct);
   _FALSE_ = lookup(fls_STR, dct); 
   _EMPTY_ = _ag_make_TAB_(0);    
   _ZERO_  = _ag_make_NBR_(0);    
   _ONE_   = _ag_make_NBR_(1);    
   _TAB_   = _env_make_NAM_(tab_STR);     
   _BEGIN_ = _env_make_NAM_(beg_STR);      
   _CONT_  = _env_make_NAM_(cnt_STR);    
   _PRD_   = _VOID_;
   _PRO_   = _ag_make_TAB_(_MAX_PRO_);
   for (ctr = 1; ctr <= _MAX_PRO_; ctr++)
	 _ag_set_TAB_EXP_(_PRO_, ctr, _VOID_);
   _ag_set_TAB_EXP_(_PRO_, 1, _ag_make_PRO_());
   _PRC_   = 1;
   _PRN_   = 1;
   return dct; }
