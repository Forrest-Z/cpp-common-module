#pragma once
#include <utility>
namespace gomros {
namespace serialize {

#define OUTINFO(arg)  coder->encode(#arg,obj.arg);

#define G_ENCODE_1(arg) OUTINFO(arg); 
#define G_ENCODE_2(arg,...) OUTINFO(arg); G_ENCODE_1(__VA_ARGS__) 
#define G_ENCODE_3(arg,...) OUTINFO(arg); G_ENCODE_2(__VA_ARGS__) 
#define G_ENCODE_4(arg,...) OUTINFO(arg); G_ENCODE_3(__VA_ARGS__) 
#define G_ENCODE_5(arg,...) OUTINFO(arg); G_ENCODE_4(__VA_ARGS__) 
#define G_ENCODE_6(arg,...) OUTINFO(arg); G_ENCODE_5(__VA_ARGS__) 
#define G_ENCODE_7(arg,...) OUTINFO(arg); G_ENCODE_6(__VA_ARGS__) 
#define G_ENCODE_8(arg,...) OUTINFO(arg); G_ENCODE_7(__VA_ARGS__) 
#define G_ENCODE_9(arg,...) OUTINFO(arg); G_ENCODE_8(__VA_ARGS__)
#define G_ENCODE_10(arg,...) OUTINFO(arg); G_ENCODE_9(__VA_ARGS__)
#define G_ENCODE_11(arg,...) OUTINFO(arg); G_ENCODE_10(__VA_ARGS__)
#define G_ENCODE_12(arg,...) OUTINFO(arg); G_ENCODE_11(__VA_ARGS__)
#define G_ENCODE_13(arg,...) OUTINFO(arg); G_ENCODE_12(__VA_ARGS__)
#define G_ENCODE_14(arg,...) OUTINFO(arg); G_ENCODE_13(__VA_ARGS__)
#define G_ENCODE_15(arg,...) OUTINFO(arg); G_ENCODE_14(__VA_ARGS__)
#define G_ENCODE_16(arg,...) OUTINFO(arg); G_ENCODE_15(__VA_ARGS__)
#define G_ENCODE_17(arg,...) OUTINFO(arg); G_ENCODE_16(__VA_ARGS__)
#define G_ENCODE_18(arg,...) OUTINFO(arg); G_ENCODE_17(__VA_ARGS__)
#define G_ENCODE_19(arg,...) OUTINFO(arg); G_ENCODE_18(__VA_ARGS__)
#define G_ENCODE_20(arg,...) OUTINFO(arg); G_ENCODE_19(__VA_ARGS__)
#define G_ENCODE_21(arg,...) OUTINFO(arg); G_ENCODE_20(__VA_ARGS__)
#define G_ENCODE_22(arg,...) OUTINFO(arg); G_ENCODE_21(__VA_ARGS__)
#define G_ENCODE_23(arg,...) OUTINFO(arg); G_ENCODE_22(__VA_ARGS__)
#define G_ENCODE_24(arg,...) OUTINFO(arg); G_ENCODE_23(__VA_ARGS__)
#define G_ENCODE_25(arg,...) OUTINFO(arg); G_ENCODE_24(__VA_ARGS__)
#define G_ENCODE_26(arg,...) OUTINFO(arg); G_ENCODE_25(__VA_ARGS__)
#define G_ENCODE_27(arg,...) OUTINFO(arg); G_ENCODE_26(__VA_ARGS__)
#define G_ENCODE_28(arg,...) OUTINFO(arg); G_ENCODE_27(__VA_ARGS__)
#define G_ENCODE_29(arg,...) OUTINFO(arg); G_ENCODE_28(__VA_ARGS__)
#define G_ENCODE_30(arg,...) OUTINFO(arg); G_ENCODE_29(__VA_ARGS__)
#define G_ENCODE_31(arg,...) OUTINFO(arg); G_ENCODE_30(__VA_ARGS__)
#define G_ENCODE_32(arg,...) OUTINFO(arg); G_ENCODE_31(__VA_ARGS__)
#define G_ENCODE_33(arg,...) OUTINFO(arg); G_ENCODE_32(__VA_ARGS__)
#define G_ENCODE_34(arg,...) OUTINFO(arg); G_ENCODE_33(__VA_ARGS__)
#define G_ENCODE_35(arg,...) OUTINFO(arg); G_ENCODE_34(__VA_ARGS__)
#define G_ENCODE_36(arg,...) OUTINFO(arg); G_ENCODE_35(__VA_ARGS__)
#define G_ENCODE_37(arg,...) OUTINFO(arg); G_ENCODE_36(__VA_ARGS__)
#define G_ENCODE_38(arg,...) OUTINFO(arg); G_ENCODE_37(__VA_ARGS__)
#define G_ENCODE_39(arg,...) OUTINFO(arg); G_ENCODE_38(__VA_ARGS__)
#define G_ENCODE_40(arg,...) OUTINFO(arg); G_ENCODE_39(__VA_ARGS__)
#define G_ENCODE_41(arg,...) OUTINFO(arg); G_ENCODE_40(__VA_ARGS__)
#define G_ENCODE_42(arg,...) OUTINFO(arg); G_ENCODE_41(__VA_ARGS__)
#define G_ENCODE_43(arg,...) OUTINFO(arg); G_ENCODE_42(__VA_ARGS__)
#define G_ENCODE_44(arg,...) OUTINFO(arg); G_ENCODE_43(__VA_ARGS__)
#define G_ENCODE_45(arg,...) OUTINFO(arg); G_ENCODE_44(__VA_ARGS__)
#define G_ENCODE_46(arg,...) OUTINFO(arg); G_ENCODE_45(__VA_ARGS__)
#define G_ENCODE_47(arg,...) OUTINFO(arg); G_ENCODE_46(__VA_ARGS__)
#define G_ENCODE_48(arg,...) OUTINFO(arg); G_ENCODE_47(__VA_ARGS__)
#define G_ENCODE_49(arg,...) OUTINFO(arg); G_ENCODE_48(__VA_ARGS__)
#define G_ENCODE_50(arg,...) OUTINFO(arg); G_ENCODE_49(__VA_ARGS__)
#define G_ENCODE_51(arg,...) OUTINFO(arg); G_ENCODE_50(__VA_ARGS__)
#define G_ENCODE_52(arg,...) OUTINFO(arg); G_ENCODE_51(__VA_ARGS__)
#define G_ENCODE_53(arg,...) OUTINFO(arg); G_ENCODE_52(__VA_ARGS__)
#define G_ENCODE_54(arg,...) OUTINFO(arg); G_ENCODE_53(__VA_ARGS__)
#define G_ENCODE_55(arg,...) OUTINFO(arg); G_ENCODE_54(__VA_ARGS__)
#define G_ENCODE_56(arg,...) OUTINFO(arg); G_ENCODE_55(__VA_ARGS__)
#define G_ENCODE_57(arg,...) OUTINFO(arg); G_ENCODE_56(__VA_ARGS__)
#define G_ENCODE_58(arg,...) OUTINFO(arg); G_ENCODE_57(__VA_ARGS__)
#define G_ENCODE_59(arg,...) OUTINFO(arg); G_ENCODE_58(__VA_ARGS__)
#define G_ENCODE_60(arg,...) OUTINFO(arg); G_ENCODE_59(__VA_ARGS__)
#define G_ENCODE_61(arg,...) OUTINFO(arg); G_ENCODE_60(__VA_ARGS__)
#define G_ENCODE_62(arg,...) OUTINFO(arg); G_ENCODE_61(__VA_ARGS__)
#define G_ENCODE_63(arg,...) OUTINFO(arg); G_ENCODE_62(__VA_ARGS__)
#define G_ENCODE_64(arg,...) OUTINFO(arg); G_ENCODE_63(__VA_ARGS__)
#define G_ENCODE_65(arg,...) OUTINFO(arg); G_ENCODE_64(__VA_ARGS__)
#define G_ENCODE_66(arg,...) OUTINFO(arg); G_ENCODE_65(__VA_ARGS__)
#define G_ENCODE_67(arg,...) OUTINFO(arg); G_ENCODE_66(__VA_ARGS__)
#define G_ENCODE_68(arg,...) OUTINFO(arg); G_ENCODE_67(__VA_ARGS__)
#define G_ENCODE_69(arg,...) OUTINFO(arg); G_ENCODE_68(__VA_ARGS__)
#define G_ENCODE_70(arg,...) OUTINFO(arg); G_ENCODE_69(__VA_ARGS__)
#define G_ENCODE_71(arg,...) OUTINFO(arg); G_ENCODE_70(__VA_ARGS__)
#define G_ENCODE_72(arg,...) OUTINFO(arg); G_ENCODE_71(__VA_ARGS__)
#define G_ENCODE_73(arg,...) OUTINFO(arg); G_ENCODE_72(__VA_ARGS__)
#define G_ENCODE_74(arg,...) OUTINFO(arg); G_ENCODE_73(__VA_ARGS__)
#define G_ENCODE_75(arg,...) OUTINFO(arg); G_ENCODE_74(__VA_ARGS__)
#define G_ENCODE_76(arg,...) OUTINFO(arg); G_ENCODE_75(__VA_ARGS__)
#define G_ENCODE_77(arg,...) OUTINFO(arg); G_ENCODE_76(__VA_ARGS__)
#define G_ENCODE_78(arg,...) OUTINFO(arg); G_ENCODE_77(__VA_ARGS__)
#define G_ENCODE_79(arg,...) OUTINFO(arg); G_ENCODE_78(__VA_ARGS__)
#define G_ENCODE_80(arg,...) OUTINFO(arg); G_ENCODE_79(__VA_ARGS__)
#define G_ENCODE_81(arg,...) OUTINFO(arg); G_ENCODE_80(__VA_ARGS__)
#define G_ENCODE_82(arg,...) OUTINFO(arg); G_ENCODE_81(__VA_ARGS__)
#define G_ENCODE_83(arg,...) OUTINFO(arg); G_ENCODE_82(__VA_ARGS__)
#define G_ENCODE_84(arg,...) OUTINFO(arg); G_ENCODE_83(__VA_ARGS__)
#define G_ENCODE_85(arg,...) OUTINFO(arg); G_ENCODE_84(__VA_ARGS__)
#define G_ENCODE_86(arg,...) OUTINFO(arg); G_ENCODE_85(__VA_ARGS__)
#define G_ENCODE_87(arg,...) OUTINFO(arg); G_ENCODE_86(__VA_ARGS__)
#define G_ENCODE_88(arg,...) OUTINFO(arg); G_ENCODE_87(__VA_ARGS__)
#define G_ENCODE_89(arg,...) OUTINFO(arg); G_ENCODE_88(__VA_ARGS__)
#define G_ENCODE_90(arg,...) OUTINFO(arg); G_ENCODE_89(__VA_ARGS__)
#define G_ENCODE_91(arg,...) OUTINFO(arg); G_ENCODE_90(__VA_ARGS__)
#define G_ENCODE_92(arg,...) OUTINFO(arg); G_ENCODE_91(__VA_ARGS__)
#define G_ENCODE_93(arg,...) OUTINFO(arg); G_ENCODE_92(__VA_ARGS__)
#define G_ENCODE_94(arg,...) OUTINFO(arg); G_ENCODE_93(__VA_ARGS__)
#define G_ENCODE_95(arg,...) OUTINFO(arg); G_ENCODE_94(__VA_ARGS__)
#define G_ENCODE_96(arg,...) OUTINFO(arg); G_ENCODE_95(__VA_ARGS__)
#define G_ENCODE_97(arg,...) OUTINFO(arg); G_ENCODE_96(__VA_ARGS__)
#define G_ENCODE_98(arg,...) OUTINFO(arg); G_ENCODE_97(__VA_ARGS__)
#define G_ENCODE_99(arg,...) OUTINFO(arg); G_ENCODE_98(__VA_ARGS__)
#define GPACK_N(_99, _98, _97, _96, _95, _94, _93, _92, _91,\
                _90, _89, _88, _87, _86, _85, _84, _83, _82, _81,     \
                _80, _79, _78, _77, _76, _75, _74, _73, _72, _71,     \
                _70, _69, _68, _67, _66, _65, _64, _63, _62, _61, _60,\
               _59, _58, _57, _56, _55, _54, _53, _52, _51, _50, _49, _48, _47, \
               _46, _45, _44, _43, _42,_41, _40, _39, _38, _37, _36,_35, _34,   \
               _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, _22, _21, \
               _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8,   \
               _7, _6, _5, _4, _3, _2, _1, N, ...) G_ENCODE##N

#define DEINFO(arg)  decoder->decode(#arg,obj.arg);

#define G_DECODE_1(arg) DEINFO(arg); 
#define G_DECODE_2(arg,...) DEINFO(arg); G_DECODE_1(__VA_ARGS__) 
#define G_DECODE_3(arg,...) DEINFO(arg); G_DECODE_2(__VA_ARGS__) 
#define G_DECODE_4(arg,...) DEINFO(arg); G_DECODE_3(__VA_ARGS__) 
#define G_DECODE_5(arg,...) DEINFO(arg); G_DECODE_4(__VA_ARGS__) 
#define G_DECODE_6(arg,...) DEINFO(arg); G_DECODE_5(__VA_ARGS__) 
#define G_DECODE_7(arg,...) DEINFO(arg); G_DECODE_6(__VA_ARGS__) 
#define G_DECODE_8(arg,...) DEINFO(arg); G_DECODE_7(__VA_ARGS__) 
#define G_DECODE_9(arg,...) DEINFO(arg); G_DECODE_8(__VA_ARGS__)
#define G_DECODE_10(arg,...) DEINFO(arg); G_DECODE_9(__VA_ARGS__)
#define G_DECODE_11(arg,...) DEINFO(arg); G_DECODE_10(__VA_ARGS__)
#define G_DECODE_12(arg,...) DEINFO(arg); G_DECODE_11(__VA_ARGS__)
#define G_DECODE_13(arg,...) DEINFO(arg); G_DECODE_12(__VA_ARGS__)
#define G_DECODE_14(arg,...) DEINFO(arg); G_DECODE_13(__VA_ARGS__)
#define G_DECODE_15(arg,...) DEINFO(arg); G_DECODE_14(__VA_ARGS__)
#define G_DECODE_16(arg,...) DEINFO(arg); G_DECODE_15(__VA_ARGS__)
#define G_DECODE_17(arg,...) DEINFO(arg); G_DECODE_16(__VA_ARGS__)
#define G_DECODE_18(arg,...) DEINFO(arg); G_DECODE_17(__VA_ARGS__)
#define G_DECODE_19(arg,...) DEINFO(arg); G_DECODE_18(__VA_ARGS__)
#define G_DECODE_20(arg,...) DEINFO(arg); G_DECODE_19(__VA_ARGS__)
#define G_DECODE_21(arg,...) DEINFO(arg); G_DECODE_20(__VA_ARGS__)
#define G_DECODE_22(arg,...) DEINFO(arg); G_DECODE_21(__VA_ARGS__)
#define G_DECODE_23(arg,...) DEINFO(arg); G_DECODE_22(__VA_ARGS__)
#define G_DECODE_24(arg,...) DEINFO(arg); G_DECODE_23(__VA_ARGS__)
#define G_DECODE_25(arg,...) DEINFO(arg); G_DECODE_24(__VA_ARGS__)
#define G_DECODE_26(arg,...) DEINFO(arg); G_DECODE_25(__VA_ARGS__)
#define G_DECODE_27(arg,...) DEINFO(arg); G_DECODE_26(__VA_ARGS__)
#define G_DECODE_28(arg,...) DEINFO(arg); G_DECODE_27(__VA_ARGS__)
#define G_DECODE_29(arg,...) DEINFO(arg); G_DECODE_28(__VA_ARGS__)
#define G_DECODE_30(arg,...) DEINFO(arg); G_DECODE_29(__VA_ARGS__)
#define G_DECODE_31(arg,...) DEINFO(arg); G_DECODE_30(__VA_ARGS__)
#define G_DECODE_32(arg,...) DEINFO(arg); G_DECODE_31(__VA_ARGS__)
#define G_DECODE_33(arg,...) DEINFO(arg); G_DECODE_32(__VA_ARGS__)
#define G_DECODE_34(arg,...) DEINFO(arg); G_DECODE_33(__VA_ARGS__)
#define G_DECODE_35(arg,...) DEINFO(arg); G_DECODE_34(__VA_ARGS__)
#define G_DECODE_36(arg,...) DEINFO(arg); G_DECODE_35(__VA_ARGS__)
#define G_DECODE_37(arg,...) DEINFO(arg); G_DECODE_36(__VA_ARGS__)
#define G_DECODE_38(arg,...) DEINFO(arg); G_DECODE_37(__VA_ARGS__)
#define G_DECODE_39(arg,...) DEINFO(arg); G_DECODE_38(__VA_ARGS__)
#define G_DECODE_40(arg,...) DEINFO(arg); G_DECODE_39(__VA_ARGS__)
#define G_DECODE_41(arg,...) DEINFO(arg); G_DECODE_40(__VA_ARGS__)
#define G_DECODE_42(arg,...) DEINFO(arg); G_DECODE_41(__VA_ARGS__)
#define G_DECODE_43(arg,...) DEINFO(arg); G_DECODE_42(__VA_ARGS__)
#define G_DECODE_44(arg,...) DEINFO(arg); G_DECODE_43(__VA_ARGS__)
#define G_DECODE_45(arg,...) DEINFO(arg); G_DECODE_44(__VA_ARGS__)
#define G_DECODE_46(arg,...) DEINFO(arg); G_DECODE_45(__VA_ARGS__)
#define G_DECODE_47(arg,...) DEINFO(arg); G_DECODE_46(__VA_ARGS__)
#define G_DECODE_48(arg,...) DEINFO(arg); G_DECODE_47(__VA_ARGS__)
#define G_DECODE_49(arg,...) DEINFO(arg); G_DECODE_48(__VA_ARGS__)
#define G_DECODE_50(arg,...) DEINFO(arg); G_DECODE_49(__VA_ARGS__)
#define G_DECODE_51(arg,...) DEINFO(arg); G_DECODE_50(__VA_ARGS__)
#define G_DECODE_52(arg,...) DEINFO(arg); G_DECODE_51(__VA_ARGS__)
#define G_DECODE_53(arg,...) DEINFO(arg); G_DECODE_52(__VA_ARGS__)
#define G_DECODE_54(arg,...) DEINFO(arg); G_DECODE_53(__VA_ARGS__)
#define G_DECODE_55(arg,...) DEINFO(arg); G_DECODE_54(__VA_ARGS__)
#define G_DECODE_56(arg,...) DEINFO(arg); G_DECODE_55(__VA_ARGS__)
#define G_DECODE_57(arg,...) DEINFO(arg); G_DECODE_56(__VA_ARGS__)
#define G_DECODE_58(arg,...) DEINFO(arg); G_DECODE_57(__VA_ARGS__)
#define G_DECODE_59(arg,...) DEINFO(arg); G_DECODE_58(__VA_ARGS__)
#define G_DECODE_60(arg,...) OUTINFO(arg); G_DECODE_59(__VA_ARGS__)
#define G_DECODE_61(arg,...) OUTINFO(arg); G_DECODE_60(__VA_ARGS__)
#define G_DECODE_62(arg,...) OUTINFO(arg); G_DECODE_61(__VA_ARGS__)
#define G_DECODE_63(arg,...) OUTINFO(arg); G_DECODE_62(__VA_ARGS__)
#define G_DECODE_64(arg,...) OUTINFO(arg); G_DECODE_63(__VA_ARGS__)
#define G_DECODE_65(arg,...) OUTINFO(arg); G_DECODE_64(__VA_ARGS__)
#define G_DECODE_66(arg,...) OUTINFO(arg); G_DECODE_65(__VA_ARGS__)
#define G_DECODE_67(arg,...) OUTINFO(arg); G_DECODE_66(__VA_ARGS__)
#define G_DECODE_68(arg,...) OUTINFO(arg); G_DECODE_67(__VA_ARGS__)
#define G_DECODE_69(arg,...) OUTINFO(arg); G_DECODE_68(__VA_ARGS__)
#define G_DECODE_70(arg,...) OUTINFO(arg); G_DECODE_69(__VA_ARGS__)
#define G_DECODE_71(arg,...) OUTINFO(arg); G_DECODE_70(__VA_ARGS__)
#define G_DECODE_72(arg,...) OUTINFO(arg); G_DECODE_71(__VA_ARGS__)
#define G_DECODE_73(arg,...) OUTINFO(arg); G_DECODE_72(__VA_ARGS__)
#define G_DECODE_74(arg,...) OUTINFO(arg); G_DECODE_73(__VA_ARGS__)
#define G_DECODE_75(arg,...) OUTINFO(arg); G_DECODE_74(__VA_ARGS__)
#define G_DECODE_76(arg,...) OUTINFO(arg); G_DECODE_75(__VA_ARGS__)
#define G_DECODE_77(arg,...) OUTINFO(arg); G_DECODE_76(__VA_ARGS__)
#define G_DECODE_78(arg,...) OUTINFO(arg); G_DECODE_77(__VA_ARGS__)
#define G_DECODE_79(arg,...) OUTINFO(arg); G_DECODE_78(__VA_ARGS__)
#define G_DECODE_80(arg,...) OUTINFO(arg); G_DECODE_79(__VA_ARGS__)
#define G_DECODE_81(arg,...) OUTINFO(arg); G_DECODE_80(__VA_ARGS__)
#define G_DECODE_82(arg,...) OUTINFO(arg); G_DECODE_81(__VA_ARGS__)
#define G_DECODE_83(arg,...) OUTINFO(arg); G_DECODE_82(__VA_ARGS__)
#define G_DECODE_84(arg,...) OUTINFO(arg); G_DECODE_83(__VA_ARGS__)
#define G_DECODE_85(arg,...) OUTINFO(arg); G_DECODE_84(__VA_ARGS__)
#define G_DECODE_86(arg,...) OUTINFO(arg); G_DECODE_85(__VA_ARGS__)
#define G_DECODE_87(arg,...) OUTINFO(arg); G_DECODE_86(__VA_ARGS__)
#define G_DECODE_88(arg,...) OUTINFO(arg); G_DECODE_87(__VA_ARGS__)
#define G_DECODE_89(arg,...) OUTINFO(arg); G_DECODE_88(__VA_ARGS__)
#define G_DECODE_90(arg,...) OUTINFO(arg); G_DECODE_89(__VA_ARGS__)
#define G_DECODE_91(arg,...) OUTINFO(arg); G_DECODE_90(__VA_ARGS__)
#define G_DECODE_92(arg,...) OUTINFO(arg); G_DECODE_91(__VA_ARGS__)
#define G_DECODE_93(arg,...) OUTINFO(arg); G_DECODE_92(__VA_ARGS__)
#define G_DECODE_94(arg,...) OUTINFO(arg); G_DECODE_93(__VA_ARGS__)
#define G_DECODE_95(arg,...) OUTINFO(arg); G_DECODE_94(__VA_ARGS__)
#define G_DECODE_96(arg,...) OUTINFO(arg); G_DECODE_95(__VA_ARGS__)
#define G_DECODE_97(arg,...) OUTINFO(arg); G_DECODE_96(__VA_ARGS__)
#define G_DECODE_98(arg,...) OUTINFO(arg); G_DECODE_97(__VA_ARGS__)
#define G_DECODE_99(arg,...) OUTINFO(arg); G_DECODE_98(__VA_ARGS__)
#define DPACK_N(_99, _98, _97, _96, _95, _94, _93, _92, _91,\
                _90, _89, _88, _87, _86, _85, _84, _83, _82, _81,     \
                _80, _79, _78, _77, _76, _75, _74, _73, _72, _71,     \
                _70, _69, _68, _67, _66, _65, _64, _63, _62, _61, _60,\
               _59, _58, _57, _56, _55, _54, _53, _52, _51, _50, _49, _48, _47, \
               _46, _45, _44, _43, _42,_41, _40, _39, _38, _37, _36,_35, _34,   \
               _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, _22, _21, \
               _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8,   \
               _7, _6, _5, _4, _3, _2, _1, N, ...) G_DECODE##N
#define ARGTYPE(x) ARGTYPE_PASS2(ARGTYPE_PASS1 x,)
//
//      => ARGTYPE_PASS2(ARGTYPE_PASS1 (ArgType) argName,)
//
#define ARGTYPE_PASS1(...) (__VA_ARGS__),
//
//      => ARGTYPE_PASS2( (ArgType), argName,)
//
#define ARGTYPE_PASS2(...) ARGTYPE_PASS3((__VA_ARGS__))
//
//      => ARGTYPE_PASS3(( (ArgType), argName,))
//
#define ARGTYPE_PASS3(x)   ARGTYPE_PASS4 x
//
//      => ARGTYPE_PASS4 ( (ArgType), argName,)
//
#define ARGTYPE_PASS4(x, ...) REM x
//
//      => REM (ArgType)
//
#define REM(...) __VA_ARGS__
//
//      => ArgType
//

//
// This counts the number of args: (0 is also supported)
//
//
//  NARGS( (ArgType1) argName1, (ArgType2) argName2 )   => 2
//
#define NARGS(...) NARGS_PASS2(NARGS_PASS1(__VA_ARGS__))
//
//  => NARGS_PASS2(NARGS_PASS1( (ArgType1) argName1, (ArgType2) argName2 ) )
//
#define NARGS_PASS1(...) unused, __VA_ARGS__
//
//  => NARGS_PASS2( unused, (ArgType1) argName1, (ArgType2) argName2 )
//
#define NARGS_PASS2(...) NARGS_PASS4(NARGS_PASS3(__VA_ARGS__, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
//
//  => NARGS_PASS4(NARGS_PASS3( unused, (ArgType1) argName1, (ArgType2) argName2 ) , 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) )
//
#define NARGS_PASS3(_unused,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,VAL, ...) VAL
//
//  => NARGS_PASS4(2)
//
#define NARGS_PASS4(x) x
//
//  => 2
//


//
// Show the type without parenthesis
//
//  ARGPAIR( (ArgType1) argName1 )                         => ArgType1 argName1
//
#define ARGPAIR(x) REM x
//
//  => REM (ArgType1) argName1
//
//  => ArgType1 argName1
//

//
// Show the type without parenthesis
//
//  ARGPAIR( (ArgType1) argName1 )                         => ArgType1 && argName1
//
#define REFARGPAIR(x) REFREM x
//
//  => REFREM (ArgType1) argName1

#define REFREM(...) __VA_ARGS__ &&
//
//  => ArgType1 && argName1
//

//
// Strip off the type
//
//  ARGNAME( (ArgType1) argName1 )                      => argName1
//
#define ARGNAME(x) EAT x
/*

*/
#define EAT(...)
//
//      => argName1
//

//
// Strip off the type
//
//  ARGNAME( (ArgType1) argName1 )                      => argName1
//
#define ARGNAME_AS_STRING(x) TOSTRING(EAT x)
//
//      => EAT (ArgType1) argName1
//
#define TOSTRING2(x)  #x
#define TOSTRING(x)   TOSTRING2(x)

// #define TOSTRING_VAL(x) std::make_pair(#x,x)
#define TOSTRING_VAL(x) #x,x

// #define TOSTRING_VAL(x) TOSTRING_VAL_PASS2(TOSTRING_TOKENS(TOSTRING_VAL_PASS1(x),x))
// #define TOSTRING_VAL_PASS1(x) TOSTRING_VAL_PASS2(TOSTRING(x))
// #define TOSTRING_VAL_PASS2(...) (__VA_ARGS__)
// #define TOSTRING_TOKENS(x, y) TOSTRING_TOKENS_PASS1((x, y))
// #define TOSTRING_TOKENS_PASS1(x) TOSTRING_CAT x
// #define TOSTRING_CAT(x, y) x y
//

// This will call a macro on each argument passed in
//
//  DOFOREACH(typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 )
//
#define DOFOREACH(macro, ...) DOFOREACH_PASS1(CAT_TOKENS(DOFOREACH_, NARGS(__VA_ARGS__)), (macro, __VA_ARGS__))
//
//          => DOFOREACH_PASS1(CAT_TOKENS(DOFOREACH_, NARGS( (ArgType1) argName1, (ArgType1) argName2 ) ), (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) ))
//          => DOFOREACH_PASS1(CAT_TOKENS(DOFOREACH_, 2), (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) ))
//
#define CAT_TOKENS(x, y) CAT_PASS1((x, y))
//
//          => DOFOREACH_PASS1(CAT_PASS1((DOFOREACH_, 2)), (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) ))
//
#define CAT_PASS1(x) PRIMITIVE_CAT x
//
//          => DOFOREACH_PASS1(PRIMITIVE_CAT (DOFOREACH_, 2), (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) ))
//
#define PRIMITIVE_CAT(x, y) x ## y
//
//          => DOFOREACH_PASS1( DOFOREACH_2 ), (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) ))
//
#define DOFOREACH_PASS1(m, x) m x
//
//          => DOFOREACH_2 (typename ARGTYPE, (ArgType1) argName1, (ArgType1) argName2 ) )
//
#define DOFOREACH_0(m)
#define DOFOREACH_1(m, x1) m(x1)
#define DOFOREACH_2(m, x1, x2) m(x1), m(x2)
//
//          => typename ARGTYPE( (ArgType1) argName1 ), typename ARGTYPE( (ArgType1) argName2 ) )
//          => typename ArgType1, typename ArgType2
//
#define DOFOREACH_3(m, x1, x2, x3) m(x1), m(x2), m(x3)
#define DOFOREACH_4(m, x1, x2, x3, x4) m(x1), m(x2), m(x3), m(x4)
#define DOFOREACH_5(m, x1, x2, x3, x4, x5) m(x1), m(x2), m(x3), m(x4), m(x5)
#define DOFOREACH_6(m, x1, x2, x3, x4, x5, x6) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6)
#define DOFOREACH_7(m, x1, x2, x3, x4, x5, x6, x7) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7)
#define DOFOREACH_8(m, x1, x2, x3, x4, x5, x6, x7, x8) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8)
#define DOFOREACH_9(m, x1, x2, x3, x4, x5, x6, x7, x8, x9) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9)
#define DOFOREACH_10(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10)
#define DOFOREACH_11(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11)
#define DOFOREACH_12(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12)
#define DOFOREACH_13(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13)
#define DOFOREACH_14(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14)
#define DOFOREACH_15(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15)
#define DOFOREACH_16(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16)
#define DOFOREACH_17(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17)
#define DOFOREACH_18(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18)
#define DOFOREACH_19(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19)
#define DOFOREACH_20(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20)
#define DOFOREACH_21(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21)
#define DOFOREACH_22(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22)
#define DOFOREACH_23(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23)
#define DOFOREACH_24(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24)
#define DOFOREACH_25(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25)
#define DOFOREACH_26(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26)
#define DOFOREACH_27(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27)
#define DOFOREACH_28(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28)
#define DOFOREACH_29(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29)
#define DOFOREACH_30(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29), m(x30)

//
//  Same version as DOFOREACH, except this one meant to be used for appending list of arguments. If 0 arguments, then list is not appended, otherwise additional command is added in front.
//
#define DOFOREACH2(macro, ...) DOFOREACH_PASS1(CAT_TOKENS(DOFOREACH2_, NARGS(__VA_ARGS__)), (macro, __VA_ARGS__))

#define DOFOREACH2_0(m)
#define DOFOREACH2_1(m, x1) ,m(x1)
#define DOFOREACH2_2(m, x1, x2) ,m(x1), m(x2)
#define DOFOREACH2_3(m, x1, x2, x3) ,m(x1), m(x2), m(x3)
#define DOFOREACH2_4(m, x1, x2, x3, x4) ,m(x1), m(x2), m(x3), m(x4)
#define DOFOREACH2_5(m, x1, x2, x3, x4, x5) ,m(x1), m(x2), m(x3), m(x4), m(x5)
#define DOFOREACH2_6(m, x1, x2, x3, x4, x5, x6) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6)
#define DOFOREACH2_7(m, x1, x2, x3, x4, x5, x6, x7) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7)
#define DOFOREACH2_8(m, x1, x2, x3, x4, x5, x6, x7, x8) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8)
#define DOFOREACH2_9(m, x1, x2, x3, x4, x5, x6, x7, x8, x9) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9)
#define DOFOREACH2_10(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10)
#define DOFOREACH2_11(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11)
#define DOFOREACH2_12(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12)
#define DOFOREACH2_13(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13)
#define DOFOREACH2_14(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14)
#define DOFOREACH2_15(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) ,m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15)
#define DOFOREACH2_16(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16)
#define DOFOREACH2_17(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17)
#define DOFOREACH2_18(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18)
#define DOFOREACH2_19(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19)
#define DOFOREACH2_20(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20)
#define DOFOREACH2_21(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21)
#define DOFOREACH2_22(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22)
#define DOFOREACH2_23(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23)
#define DOFOREACH2_24(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24)
#define DOFOREACH2_25(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25)
#define DOFOREACH2_26(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26)
#define DOFOREACH2_27(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27)
#define DOFOREACH2_28(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28)
#define DOFOREACH2_29(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29)
#define DOFOREACH2_30(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29), m(x30)


//
//  Same version as DOFOREACH, uses ';' separation for fields. Can be used to reflect fields or function calls.
//
#define DOFOREACH_SEMICOLON(macro, ...) DOFOREACH_PASS1(CAT_TOKENS(DOFOREACH_SEMICOLON_, NARGS(__VA_ARGS__)), (macro, __VA_ARGS__))

#define DOFOREACH_SEMICOLON_0(m)
#define DOFOREACH_SEMICOLON_1(m, x1) m(x1);
#define DOFOREACH_SEMICOLON_2(m, x1, x2) m(x1); m(x2);
#define DOFOREACH_SEMICOLON_3(m, x1, x2, x3) m(x1); m(x2); m(x3);
#define DOFOREACH_SEMICOLON_4(m, x1, x2, x3, x4) m(x1); m(x2); m(x3); m(x4);
#define DOFOREACH_SEMICOLON_5(m, x1, x2, x3, x4, x5) m(x1); m(x2); m(x3); m(x4); m(x5);
#define DOFOREACH_SEMICOLON_6(m, x1, x2, x3, x4, x5, x6)  m(x1); m(x2); m(x3); m(x4); m(x5); m(x6);
#define DOFOREACH_SEMICOLON_7(m, x1, x2, x3, x4, x5, x6, x7) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7);
#define DOFOREACH_SEMICOLON_8(m, x1, x2, x3, x4, x5, x6, x7, x8) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8);
#define DOFOREACH_SEMICOLON_9(m, x1, x2, x3, x4, x5, x6, x7, x8, x9) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9);
#define DOFOREACH_SEMICOLON_10(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10);
#define DOFOREACH_SEMICOLON_11(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10); m(x11);
#define DOFOREACH_SEMICOLON_12(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10); m(x11); m(x12);
#define DOFOREACH_SEMICOLON_13(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10); m(x11); m(x12); m(x13);
#define DOFOREACH_SEMICOLON_14(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10); m(x11); m(x12); m(x13); m(x14);
#define DOFOREACH_SEMICOLON_15(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) m(x1); m(x2); m(x3); m(x4); m(x5); m(x6); m(x7); m(x8); m(x9); m(x10); m(x11); m(x12); m(x13); m(x14); m(x15);
#define DOFOREACH_SEMICOLON_16(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16)
#define DOFOREACH_SEMICOLON_17(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17)
#define DOFOREACH_SEMICOLON_18(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18)
#define DOFOREACH_SEMICOLON_19(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19)
#define DOFOREACH_SEMICOLON_20(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20)
#define DOFOREACH_SEMICOLON_21(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21)
#define DOFOREACH_SEMICOLON_22(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22)
#define DOFOREACH_SEMICOLON_23(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23)
#define DOFOREACH_SEMICOLON_24(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24)
#define DOFOREACH_SEMICOLON_25(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25)
#define DOFOREACH_SEMICOLON_26(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26)
#define DOFOREACH_SEMICOLON_27(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27)
#define DOFOREACH_SEMICOLON_28(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28)
#define DOFOREACH_SEMICOLON_29(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29)
#define DOFOREACH_SEMICOLON_30(m, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30) m(x1), m(x2), m(x3), m(x4), m(x5), m(x6), m(x7), m(x8), m(x9), m(x10), m(x11), m(x12), m(x13), m(x14), m(x15), m(x16), m(x17), m(x18), m(x19), m(x20), m(x21), m(x22), m(x23), m(x24), m(x25), m(x26), m(x27), m(x28), m(x29), m(x30)


//
//  ARGX(1)     =>      (Arg1) arg1
//
#define ARGX(index) (Arg##index) arg##index

//
//  Defines same function with different amount of arguments.
//
#define DEFINE_MULTIARG_FUNC(macro) \
    macro ( ARGX(1) ); \
    macro ( ARGX(1), ARGX(2) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28), ARGX(29)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28), ARGX(29), ARGX(30)  ); \
//
//  Same as previous, except add support also of function with no arguments.
//  (template functions normally requires at least one template parameter (so you write template<> in front of function and won't get error), that's why separate define)
//
#define DEFINE_MULTIARG_FUNC2(macro) \
    macro ( ); \
    macro ( ARGX(1) ); \
    macro ( ARGX(1), ARGX(2) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12) ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28), ARGX(29)  ); \
    macro ( ARGX(1), ARGX(2), ARGX(3), ARGX(4), ARGX(5), ARGX(6), ARGX(7), ARGX(8), ARGX(9), ARGX(10), ARGX(11), ARGX(12), ARGX(13), ARGX(14), ARGX(15), ARGX(16), ARGX(17), ARGX(18), ARGX(19), ARGX(20), ARGX(21), ARGX(22), ARGX(23), ARGX(24), ARGX(25), ARGX(26), ARGX(27), ARGX(28), ARGX(29), ARGX(30)  ); \

}  // namespace serialize
}  // namespace gomros