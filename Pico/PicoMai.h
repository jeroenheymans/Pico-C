/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/
/*           Main program            */
/*-----------------------------------*/

#define NDEBUG

#include <string.h> // for strlen
#include <float.h>
#include <limits.h>
#include <setjmp.h>

/* private constants */

#define FUN_NAM_INDEX 1
#define FUN_ARG_INDEX 2
#define FUN_EXP_INDEX 3
#define FUN_DCT_INDEX 4

#define NAT_NAM_INDEX 1
#define NAT_NBR_INDEX 2

#define VAR_NAM_INDEX 1

#define APL_NAM_INDEX 1
#define APL_ARG_INDEX 2

#define TBL_NAM_INDEX 1
#define TBL_IDX_INDEX 2

#define DEF_INV_INDEX 1
#define DEF_EXP_INDEX 2

#define SET_INV_INDEX 1
#define SET_EXP_INDEX 2

#define DCT_NAM_INDEX 1
#define DCT_VAL_INDEX 2
#define DCT_DCT_INDEX 3

#define ENV_DCT_INDEX 1
#define ENV_BOT_INDEX 2
#define ENV_TOP_INDEX 3
#define ENV_TAB_INDEX 4

#define THA_INV_INDEX 1
#define THA_NAM_INDEX 2
#define THA_ARG_INDEX 3

#define THQ_NAM_INDEX 1
#define THQ_INV_INDEX 2
#define THQ_ARG_INDEX 3

#define THR_IDF_INDEX 1
#define THR_EXP_INDEX 2
#define THR_ENV_INDEX 3

#define TID_IDF_INDEX 1

#define SCH_THR_INDEX 1
#define SCH_SCH_INDEX 2

/* public constants */

#define _GLOBAL_SIZE_ 4000

#define _EXP_SIZE_    sizeof(_EXP_TYPE_)
#define _FRC_SIZE_    sizeof(_FLO_TYPE_)

#define _FRC_MIN_     DBL_MIN
#define _FRC_MAX_     DBL_MAX
#define _NBR_MAX_     (LONG_MAX>>1)

#define _STK_CLAIM_   24
#define _MEM_CLAIM_   10

#define _MAX_SES_     10
#define _STK_INIT_    64
#define _STK_FRACT_   0.05
#define _NAM_FRACT_   0.05
#define _BUF_SIZE_    32768

#define _VOI_SIZE_    0
#define _NAT_SIZE_    2
#define _FUN_SIZE_    4
#define _VAR_SIZE_    1
#define _APL_SIZE_    2
#define _TBL_SIZE_    2
#define _DEF_SIZE_    2
#define _SET_SIZE_    2
#define _DCT_SIZE_    3
#define _ENV_SIZE_    4
#define _THA_SIZE_    3
#define _THQ_SIZE_    3
#define _THR_SIZE_    3
#define _TID_SIZE_    1
#define _SCH_SIZE_    2

/* private macros */

#ifdef NDEBUG

#define CHK_AGR(AGR, TAG) (AGR)
  
#endif

/* public macros */

#define _ag_make_VOI_()\
  _mem_make_chunk_(_VOI_SIZE_, _VOI_TAG_)  
                               
#define _ag_make_NBR_(SGN)\
  _mem_make_nbr_(SGN)                            
                               
#define _ag_make_NBU_(UNS)\
  _mem_make_nbu_(UNS)    
                               
#define _ag_make_FRC_(FLP)\
  _mem_fill_raw_(_FRC_SIZE_, _FRC_TAG_, (void *)FLP)

#define _ag_make_TXT_(STR)\
  _mem_fill_raw_(strlen(STR) + 1, _TXT_TAG_, (void *)STR)

#define _ag_make_TAB_(SIZ)\
  _mem_make_chunk_(SIZ, _TAB_TAG_)                  

#define _ag_make_FUN_()\
  _mem_make_chunk_(_FUN_SIZE_, _FUN_TAG_)             

#define _ag_make_NAT_()\
  _mem_make_chunk_(_NAT_SIZE_, _NAT_TAG_)            

#define _ag_make_VAR_()\
  _mem_make_chunk_(_VAR_SIZE_, _VAR_TAG_)      

#define _ag_make_APL_()\
  _mem_make_chunk_(_APL_SIZE_, _APL_TAG_)              

#define _ag_make_TBL_()\
  _mem_make_chunk_(_TBL_SIZE_, _TBL_TAG_)              
   
#define _ag_make_DEF_()\
  _mem_make_chunk_(_DEF_SIZE_, _DEF_TAG_)             
   
#define _ag_make_SET_()\
  _mem_make_chunk_(_SET_SIZE_, _SET_TAG_) 
  
#define _ag_make_DCT_()\
  _mem_make_chunk_(_DCT_SIZE_, _DCT_TAG_)       

#define _ag_make_ENV_()\
  _mem_make_chunk_(_ENV_SIZE_, _ENV_TAG_)      

#define _ag_make_THA_()\
  _mem_make_chunk_(_THA_SIZE_, _THA_TAG_)    

#define _ag_make_THQ_()\
  _mem_make_chunk_(_THQ_SIZE_, _THQ_TAG_)       

#define _ag_make_THR_()\
  _mem_make_chunk_(_THR_SIZE_, _THR_TAG_)    

#define _ag_make_TID_()\
  _mem_make_chunk_(_TID_SIZE_, _TID_TAG_)

#define _ag_make_SCH_()\
  _mem_make_chunk_(_SCH_SIZE_, _SCH_TAG_)

#define _ag_get_TAG_(AGR)\
 ((_mem_is_number_(AGR))\
    ? _NBR_TAG_ : _mem_get_tag_(AGR))
      
#define _ag_get_FRC_(FRC)\
 (_FLP_TYPE_)_mem_cast_raw_(FRC, _FRC_TAG_)
    
#define _ag_get_TXT_(TXT)\
 (_STR_TYPE_)_mem_cast_raw_(TXT, _TXT_TAG_)
 
#define _ag_get_NAT_NAM_(NAT)\
 _mem_get_exp_(CHK_AGR(NAT, _NAT_TAG_), NAT_NAM_INDEX)
   
#define _ag_get_NAT_NBR_(NAT)\
 _mem_get_exp_(CHK_AGR(NAT, _NAT_TAG_), NAT_NBR_INDEX)
   
#define _ag_get_TAB_SIZ_(TAB)\
 _mem_chunk_size_(TAB)
  
#define _ag_get_TAB_EXP_(TAB, IDX)\
 _mem_get_exp_(TAB, IDX)

#define _ag_get_TAB_CNT_(TAB, IDX)\
 _mem_get_cnt_(TAB, IDX)

#define _ag_get_NBR_(NBR)\
 _mem_get_nbr_(CHK_AGR(NBR, _NBR_TAG_))
 
#define _ag_get_NBU_(NBR)\
 _mem_get_nbu_(CHK_AGR(NBR, _NBR_TAG_))
 
#define _ag_get_FUN_NAM_(FUN)\
 _mem_get_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_NAM_INDEX)
   
#define _ag_get_FUN_ARG_(FUN)\
 _mem_get_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_ARG_INDEX)
   
#define _ag_get_FUN_EXP_(FUN)\
 _mem_get_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_EXP_INDEX)

#define _ag_get_FUN_DCT_(FUN)\
 _mem_get_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_DCT_INDEX)
 
#define _ag_get_VAR_NAM_(VAR)\
 _mem_get_exp_(CHK_AGR(VAR, _VAR_TAG_), VAR_NAM_INDEX)

#define _ag_get_APL_NAM_(APL)\
 _mem_get_exp_(CHK_AGR(APL, _APL_TAG_), APL_NAM_INDEX)

#define _ag_get_APL_ARG_(APL)\
 _mem_get_exp_(CHK_AGR(APL, _APL_TAG_), APL_ARG_INDEX)

#define _ag_get_TBL_NAM_(TBL)\
 _mem_get_exp_(CHK_AGR(TBL, _TBL_TAG_), TBL_NAM_INDEX)

#define _ag_get_TBL_IDX_(TBL)\
 _mem_get_exp_(CHK_AGR(TBL, _TBL_TAG_), TBL_IDX_INDEX)

#define _ag_get_DEF_INV_(DEF)\
 _mem_get_exp_(CHK_AGR(DEF, _DEF_TAG_), DEF_INV_INDEX)

#define _ag_get_DEF_EXP_(DEF)\
 _mem_get_exp_(CHK_AGR(DEF, _DEF_TAG_), DEF_EXP_INDEX)

#define _ag_get_SET_INV_(SET)\
 _mem_get_exp_(CHK_AGR(SET, _SET_TAG_), SET_INV_INDEX)

#define _ag_get_SET_EXP_(SET)\
 _mem_get_exp_(CHK_AGR(SET, _SET_TAG_), SET_EXP_INDEX)
 
#define _ag_get_DCT_NAM_(DCT)\
 _mem_get_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_NAM_INDEX)

#define _ag_get_DCT_VAL_(DCT)\
 _mem_get_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_VAL_INDEX)

#define _ag_get_DCT_DCT_(DCT)\
 _mem_get_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_DCT_INDEX)

#define _ag_get_ENV_DCT_(ENV)\
 _mem_get_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_DCT_INDEX)

#define _ag_get_ENV_BOT_(ENV)\
 _mem_get_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_BOT_INDEX)

#define _ag_get_ENV_TOP_(ENV)\
 _mem_get_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_TOP_INDEX)

#define _ag_get_ENV_TAB_(ENV)\
 _mem_get_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_TAB_INDEX)

#define _ag_get_THA_INV_(THA)\
 _mem_get_exp_(CHK_AGR(THA, _THA_TAG_), THA_INV_INDEX)

#define _ag_get_THA_NAM_(THA)\
 _mem_get_exp_(CHK_AGR(THA, _THA_TAG_), THA_NAM_INDEX)

#define _ag_get_THA_ARG_(THA)\
 _mem_get_exp_(CHK_AGR(THA, _THA_TAG_), THA_ARG_INDEX)

#define _ag_get_THQ_INV_(THQ)\
 _mem_get_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_INV_INDEX)

#define _ag_get_THQ_NAM_(THQ)\
 _mem_get_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_NAM_INDEX)

#define _ag_get_THQ_ARG_(THQ)\
 _mem_get_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_ARG_INDEX)

#define _ag_get_THR_IDF_(THR)\
 _mem_get_exp_(CHK_AGR(THR, _THR_TAG_), THR_IDF_INDEX)

#define _ag_get_THR_EXP_(THR)\
 _mem_get_exp_(CHK_AGR(THR, _THR_TAG_), THR_EXP_INDEX)

#define _ag_get_THR_ENV_(THR)\
 _mem_get_exp_(CHK_AGR(THR, _THR_TAG_), THR_ENV_INDEX)

#define _ag_get_TID_IDF_(TID)\
 _mem_get_exp_(CHK_AGR(TID, _TID_TAG_), TID_IDF_INDEX)

#define _ag_get_SCH_THR_(SCH)\
 _mem_get_exp_(CHK_AGR(SCH, _SCH_TAG_), SCH_THR_INDEX)

#define _ag_get_SCH_SCH_(SCH)\
 _mem_get_exp_(CHK_AGR(SCH, _SCH_TAG_), SCH_SCH_INDEX)

#define _ag_succ_NBR_(NBR)\
  _mem_succ_number_(NBR)                            
                               
#define _ag_set_NAT_NAM_(NAT, NAM)\
 _mem_set_exp_(CHK_AGR(NAT, _NAT_TAG_), NAT_NAM_INDEX, NAM)
   
#define _ag_set_NAT_NBR_(NAT, NBR)\
 _mem_set_exp_(CHK_AGR(NAT, _NAT_TAG_), NAT_NBR_INDEX, NBR)
   
#define _ag_set_TAB_EXP_(TAB, IDX, EXP)\
 _mem_set_exp_(TAB, IDX, EXP)
 
#define _ag_set_TAB_CNT_(TAB, IDX, CNT)\
 _mem_set_cnt_(TAB, IDX, CNT)

#define _ag_set_FUN_NAM_(FUN, NAM)\
 _mem_set_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_NAM_INDEX, NAM)
   
#define _ag_set_FUN_ARG_(FUN, ARG)\
 _mem_set_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_ARG_INDEX, ARG)
   
#define _ag_set_FUN_EXP_(FUN, EXP)\
 _mem_set_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_EXP_INDEX, EXP)

#define _ag_set_FUN_DCT_(FUN, DCT)\
 _mem_set_exp_(CHK_AGR(FUN, _FUN_TAG_), FUN_DCT_INDEX, DCT)
 
#define _ag_set_VAR_NAM_(VAR, NAM)\
 _mem_set_exp_(CHK_AGR(VAR, _VAR_TAG_), VAR_NAM_INDEX, NAM)

#define _ag_set_APL_NAM_(APL, NAM)\
 _mem_set_exp_(CHK_AGR(APL, _APL_TAG_), APL_NAM_INDEX, NAM)

#define _ag_set_APL_ARG_(APL, ARG)\
 _mem_set_exp_(CHK_AGR(APL, _APL_TAG_), APL_ARG_INDEX, ARG)

#define _ag_set_TBL_NAM_(TBL, NAM)\
 _mem_set_exp_(CHK_AGR(TBL, _TBL_TAG_), TBL_NAM_INDEX, NAM)

#define _ag_set_TBL_IDX_(TBL, IDX)\
 _mem_set_exp_(CHK_AGR(TBL, _TBL_TAG_), TBL_IDX_INDEX, IDX)

#define _ag_set_DEF_INV_(DEF, REF)\
 _mem_set_exp_(CHK_AGR(DEF, _DEF_TAG_), DEF_INV_INDEX, REF)

#define _ag_set_DEF_EXP_(DEF, EXP)\
 _mem_set_exp_(CHK_AGR(DEF, _DEF_TAG_), DEF_EXP_INDEX, EXP)

#define _ag_set_SET_INV_(SET, REF)\
 _mem_set_exp_(CHK_AGR(SET, _SET_TAG_), SET_INV_INDEX, REF)

#define _ag_set_SET_EXP_(SET, EXP)\
 _mem_set_exp_(CHK_AGR(SET, _SET_TAG_), SET_EXP_INDEX, EXP)

#define _ag_set_DCT_NAM_(DCT, NAM)\
 _mem_set_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_NAM_INDEX, NAM)

#define _ag_set_DCT_VAL_(DCT, VAL)\
 _mem_set_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_VAL_INDEX, VAL)

#define _ag_set_DCT_DCT_(DCT, DCX)\
 _mem_set_exp_(CHK_AGR(DCT, _DCT_TAG_), DCT_DCT_INDEX, DCX)

#define _ag_set_ENV_DCT_(ENV, DCT)\
 _mem_set_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_DCT_INDEX, DCT)

#define _ag_set_ENV_BOT_(ENV, LWR)\
 _mem_set_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_BOT_INDEX, LWR)

#define _ag_set_ENV_TOP_(ENV, UPR)\
 _mem_set_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_TOP_INDEX, UPR)

#define _ag_set_ENV_TAB_(ENV, TAB)\
 _mem_set_exp_(CHK_AGR(ENV, _ENV_TAG_), ENV_TAB_INDEX, TAB)

#define _ag_set_THA_INV_(THA, INV)\
 _mem_set_exp_(CHK_AGR(THA, _THA_TAG_), THA_INV_INDEX, INV)

#define _ag_set_THA_NAM_(THA, NAM)\
 _mem_set_exp_(CHK_AGR(THA, _THA_TAG_), THA_NAM_INDEX, NAM)

#define _ag_set_THA_ARG_(THA, ARG)\
 _mem_set_exp_(CHK_AGR(THA, _THA_TAG_), THA_ARG_INDEX, ARG)

#define _ag_set_THQ_INV_(THQ, INV)\
 _mem_set_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_INV_INDEX, INV)

#define _ag_set_THQ_NAM_(THQ, NAM)\
 _mem_set_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_NAM_INDEX, NAM)

#define _ag_set_THQ_ARG_(THQ, ARG)\
 _mem_set_exp_(CHK_AGR(THQ, _THQ_TAG_), THQ_ARG_INDEX, ARG)

#define _ag_set_THR_IDF_(THR, IDF)\
 _mem_set_exp_(CHK_AGR(THR, _THR_TAG_), THR_IDF_INDEX, IDF)

#define _ag_set_THR_EXP_(THR, EXP)\
 _mem_set_exp_(CHK_AGR(THR, _THR_TAG_), THR_EXP_INDEX, EXP)

#define _ag_set_THR_ENV_(THR, ENV)\
 _mem_set_exp_(CHK_AGR(THR, _THR_TAG_), THR_ENV_INDEX, ENV)

#define _ag_set_TID_IDF_(TID, IDF)\
 _mem_set_exp_(CHK_AGR(TID, _TID_TAG_), TID_IDF_INDEX, IDF)

#define _ag_set_SCH_THR_(SCH, THR)\
 _mem_set_exp_(CHK_AGR(SCH, _SCH_TAG_), SCH_THR_INDEX, THR)

#define _ag_set_SCH_SCH_(SCH, SCX)\
 _mem_set_exp_(CHK_AGR(SCH, _SCH_TAG_), SCH_SCH_INDEX, SCX)

#define _ag_is_VOI_(VOI)\
 (_mem_get_tag_(VOI) == _VOI_TAG_)
 
#define _ESCAPE_\
   if (!_DELAY_--) _escape_()

/* public types */

typedef unsigned int      _UNS_TYPE_;
typedef   signed int      _SGN_TYPE_; 
typedef          double   _FLO_TYPE_;                    
typedef          double * _FLP_TYPE_;     
typedef unsigned char     _BYT_TYPE_;
typedef unsigned char     _CHA_TYPE_;  
typedef          jmp_buf  _EXI_TYPE_;

typedef enum { _VOI_TAG_ = 0 ,
               _NAT_TAG_ = 1 ,
               _FRC_TAG_ = 2 ,
               _TXT_TAG_ = 3 ,
               _TAB_TAG_ = 4 ,
               _FUN_TAG_ = 5 ,
               _VAR_TAG_ = 6 ,
               _APL_TAG_ = 7 ,
               _TBL_TAG_ = 8 ,
               _DEF_TAG_ = 9 ,
               _SET_TAG_ = 10,
               _DCT_TAG_ = 11,
               _ENV_TAG_ = 12,
               _NY1_TAG_ = 13,
               _NY2_TAG_ = 14,
               _NY3_TAG_ = 15,
               _NBR_TAG_ = 16,
               _THA_TAG_ = 17,
               _THQ_TAG_ = 18,
               _THR_TAG_ = 19,
               _TID_TAG_ = 20 ,
               _SCH_TAG_ = 21 } _TAG_TYPE_;

typedef          char     _BUF_TYPE_[_BUF_SIZE_];

typedef _SGN_TYPE_ (*_SGN_COMP_)(const _SGN_TYPE_,
                                 const _SGN_TYPE_);
typedef _SGN_TYPE_ (*_FLO_COMP_)(const _FLO_TYPE_,
                                 const _FLO_TYPE_);
typedef _SGN_TYPE_ (*_STR_COMP_)(const _STR_TYPE_,
                                 const _STR_TYPE_);
typedef _NIL_TYPE_ (*_CNT_TYPE_)(      _NIL_TYPE_);

typedef struct { _UNS_TYPE_ siz: 23;
                 _UNS_TYPE_ tag:  5;
                 _UNS_TYPE_ raw:  1;
                 _UNS_TYPE_ hdr:  1;
                 _UNS_TYPE_ bsy:  1;
                 _UNS_TYPE_ ptr:  1; } _HDR_TYPE_;

typedef struct { _UNS_TYPE_ ofs: 29;
                 _UNS_TYPE_ hdr:  1;
                 _UNS_TYPE_ bsy:  1;
                 _UNS_TYPE_ ptr:  1; } _PTR_TYPE_;

typedef struct { _SGN_TYPE_ nbr: 31;
 	  		         _UNS_TYPE_ ptr:  1; } _NBR_TYPE_;
 	  		         
typedef struct { _UNS_TYPE_ nbr: 31;
 	  		         _UNS_TYPE_ ptr:  1; } _NBU_TYPE_;
 	  		         
typedef struct { _UNS_TYPE_ pfx: 28;
 	  		         _UNS_TYPE_ sta:  4; } _SWI_TYPE_;
 	  		         
typedef  union { _HDR_TYPE_ hdr;
                 _PTR_TYPE_ ptr;
                 _CNT_TYPE_ cnt;
                 _UNS_TYPE_ raw; 
                 _NBR_TYPE_ nbr;
                 _NBU_TYPE_ nbu;
                 _SWI_TYPE_ swi;     } _EXP_TYPE_;

typedef struct { _SES_TYPE_ ses;
                 _RES_TYPE_ res;
                 _EXI_TYPE_ exi;
                 _EXP_TYPE_ dct; 
                 _EXP_TYPE_ esc; } _DSC_TYPE_;

/* public variables */

extern _BYT_TYPE_ _DELAY_;
extern _BUF_TYPE_ _TEXT_BUF_;
extern _UNS_TYPE_ _STK_MAX_;
extern _EXP_TYPE_ _NAMES_;

/* public prototypes */

_NIL_TYPE_     _print_(const _STR_TYPE_);

_NIL_TYPE_     _error_(const _RES_TYPE_);

_NIL_TYPE_   _reclaim_(const _UNS_TYPE_);

_NIL_TYPE_ _error_str_(const _RES_TYPE_,
                       const _STR_TYPE_);
                       
_NIL_TYPE_ _error_msg_(const _RES_TYPE_,
                       const _EXP_TYPE_);
                       
_NIL_TYPE_      _mark_(const _POS_TYPE_ ,
                       const _POS_TYPE_);
                       
_NIL_TYPE_    _escape_(      _NIL_TYPE_);

_NIL_TYPE_    _accept_(      _NIL_TYPE_);

_NIL_TYPE_      _load_(const _STR_TYPE_);

_NIL_TYPE_   _display_(const _STR_TYPE_);

#ifndef NDEBUG

_EXP_TYPE_     CHK_AGR(const _EXP_TYPE_,
                       const _TAG_TYPE_);
  
#endif

