#pragma once
#include <QStringList>
#include <vector>

//#define USE_ARRAY

enum Phonetics {
    C = 0,      // consonant            согласная
    V,          // vowel                гласная
    D,          // diphthongs           йотированные гласные
    CV,
    CVD,        // soft consonants      мягкие согласные
    SmallTSU,
    N
};

enum SymbolEnum {
    Hiragana = 0,
    Katakana,
    PhoneticsENG,
    PhoneticsRUS
};

struct Symbol {
    Phonetics   phonetics;
    QStringList text;
};
using SymVec = std::vector<Symbol>;
using PhoVec = std::vector<Phonetics>;

static const QChar DoubleVowelSign = ':';
//static const Symbol LongVowel       = {Phonetics::V, {"ー"}}
static Symbol   SmallTsu    = {Phonetics::SmallTSU, {"っ", "ッ", "", ""}};
static Symbol   NN          = {Phonetics::N, {"ん", "ン", "nn", "нн"}};

static QString  shi_eng = "shi";    // si
static QString  shi_rus = "ши";     // си

static QString  chi_eng = "chi";    // di
static QString  chi_rus = "чи";     // дзи
static QString  di_eng  = "di";
static QString  di_rus  = "ди";

static QString  tsu_eng = "tsu";    // tu
static QString  tsu_rus = "цу";     // дзу
static QString  du_eng  = "du";
static QString  du_rus  = "ду";

#ifdef USE_ARRAY
#else
#endif

#ifdef USE_ARRAY
static Symbol Column1[] =
#else
static SymVec Column1 =
#endif
{
    {Phonetics::V, {"あ", "ア", "a", "а"}},
    {Phonetics::V, {"い", "イ", "i", "и"}},
    {Phonetics::V, {"う", "ウ", "u", "у"}},
    {Phonetics::V, {"え", "エ", "e", "э"}},
    {Phonetics::V, {"お", "オ", "o", "о"}}
};

#ifdef USE_ARRAY
static Symbol Column2_K[] =
#else
static SymVec Column2_K =
#endif
{
    {Phonetics::CV, {"か", "カ", "ka", "ка"}},
    {Phonetics::CV, {"き", "キ", "ki", "ки"}},
    {Phonetics::CV, {"く", "ク", "ku", "ку"}},
    {Phonetics::CV, {"け", "ケ", "ke", "кэ"}},
    {Phonetics::CV, {"こ", "コ", "ko", "ко"}}
};

#ifdef USE_ARRAY
static Symbol Column2_G[] =
#else
static SymVec Column2_G =
#endif
{
    {Phonetics::CV, {"が", "ガ", "ga", "га"}},
    {Phonetics::CV, {"ぎ", "ギ", "gi", "ги"}},
    {Phonetics::CV, {"ぐ", "グ", "gu", "гу"}},
    {Phonetics::CV, {"げ", "ゲ", "ge", "гэ"}},
    {Phonetics::CV, {"ご", "ゴ", "go", "го"}}
};

#ifdef USE_ARRAY
static Symbol Column3_S[] =
#else
static SymVec Column3_S =
#endif
{
    {Phonetics::CV, {"さ", "サ", "sa", "са"}},
    {Phonetics::CV, {"し", "シ", shi_eng, shi_rus}},
    {Phonetics::CV, {"す", "ス", "su", "су"}},
    {Phonetics::CV, {"せ", "セ", "se", "сэ"}},
    {Phonetics::CV, {"そ", "ソ", "so", "со"}}
};

#ifdef USE_ARRAY
static Symbol Column3_Z[] =
#else
static SymVec Column3_Z =
#endif
{
    {Phonetics::CV, {"ざ", "ザ", "za", "дза"}},
    {Phonetics::CV, {"じ", "ジ", "ji", "дзи"}},
    {Phonetics::CV, {"ず", "ズ", "zu", "дзу"}},
    {Phonetics::CV, {"ぜ", "ズ", "ze", "дзэ"}},
    {Phonetics::CV, {"ぞ", "ゾ", "zo", "дзо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_T[] =
#else
static SymVec Column4_T =
#endif
{
    {Phonetics::CV, {"た", "タ", "ta", "та"}},
    {Phonetics::CV, {"ち", "チ", chi_eng, chi_rus}},
    {Phonetics::CV, {"つ", "ツ", tsu_eng, tsu_rus}},
    {Phonetics::CV, {"て", "テ", "te", "тэ"}},
    {Phonetics::CV, {"と", "テ", "to", "то"}}
};

#ifdef USE_ARRAY
static Symbol Column4_D[] =
#else
static SymVec Column4_D =
#endif
{
    {Phonetics::CV, {"だ", "ダ", "da", "да"}},
    {Phonetics::CV, {"ぢ", "ヂ", di_eng, di_rus}},
    {Phonetics::CV, {"づ", "ヅ", du_eng, du_rus}},
    {Phonetics::CV, {"で", "デ", "de", "дэ"}},
    {Phonetics::CV, {"ど", "ド", "do", "до"}}
};

#ifdef USE_ARRAY
static Symbol Column5_N[] =
#else
static SymVec Column5_N =
#endif
{
    {Phonetics::CV, {"な", "ナ", "na", "на"}},
    {Phonetics::CV, {"に", "ニ", "ni", "ни"}},
    {Phonetics::CV, {"ぬ", "ヌ", "nu", "ну"}},
    {Phonetics::CV, {"ね", "ネ", "ne", "нэ"}},
    {Phonetics::CV, {"の", "ノ", "no", "но"}}
};

#ifdef USE_ARRAY
static Symbol Column6_H[] =
#else
static SymVec Column6_H =
#endif
{
    {Phonetics::CV, {"は", "ハ", "ha", "ха"}},
    {Phonetics::CV, {"ひ", "ヒ", "hi", "хи"}},
    {Phonetics::CV, {"ふ", "フ", "fu", "фу"}},
    {Phonetics::CV, {"へ", "ヘ", "he", "хэ"}},
    {Phonetics::CV, {"ほ", "ホ", "ho", "хо"}}
};

#ifdef USE_ARRAY
static Symbol Column6_B[] =
#else
static SymVec Column6_B =
#endif
{
    {Phonetics::CV, {"ば", "バ", "ba", "ба"}},
    {Phonetics::CV, {"び", "ビ", "bi", "би"}},
    {Phonetics::CV, {"ぶ", "ブ", "bu", "бу"}},
    {Phonetics::CV, {"べ", "ボ", "be", "бэ"}},
    {Phonetics::CV, {"ぼ", "ベ", "bo", "бо"}}
};

#ifdef USE_ARRAY
static Symbol Column6_P[] =
#else
static SymVec Column6_P =
#endif
{
    {Phonetics::CV, {"ぱ", "パ", "pa", "па"}},
    {Phonetics::CV, {"ぴ", "ピ", "pi", "пи"}},
    {Phonetics::CV, {"ぷ", "プ", "pu", "пу"}},
    {Phonetics::CV, {"ぺ", "ポ", "pe", "пэ"}},
    {Phonetics::CV, {"ぽ", "ペ", "po", "по"}}
};

#ifdef USE_ARRAY
static Symbol Column7_M[] =
#else
static SymVec Column7_M =
#endif
{
     {Phonetics::CV, {"ま", "マ", "ma", "ма"}},
     {Phonetics::CV, {"み", "ミ", "mi", "ми"}},
     {Phonetics::CV, {"む", "ム", "mu", "му"}},
     {Phonetics::CV, {"め", "メ", "me", "мэ"}},
     {Phonetics::CV, {"も", "モ", "mo", "мо"}}
};

#ifdef USE_ARRAY
static Symbol Column8_Y[] =
#else
static SymVec Column8_Y =
#endif
{
     {Phonetics::D, {"や", "ヤ", "ya", "я"}},
     {Phonetics::D, {"ゆ", "ユ", "yu", "ю"}},
     {Phonetics::D, {"よ", "ヨ", "yo", "ё"}}
};

#ifdef USE_ARRAY
static Symbol Column9_R[] =
#else
static SymVec Column9_R =
#endif
{
     {Phonetics::CV, {"ら", "ラ", "ra", "ра"}},
     {Phonetics::CV, {"り", "リ", "ri", "ри"}},
     {Phonetics::CV, {"る", "ル", "ru", "ру"}},
     {Phonetics::CV, {"れ", "レ", "re", "рэ"}},
     {Phonetics::CV, {"ろ", "ロ", "ro", "ро"}}
};

#ifdef USE_ARRAY
static Symbol Column10_W[] =
#else
static SymVec Column10_W =
#endif
{
     {Phonetics::CV, {"わ", "ワ", "wa", "ва"}},
     {Phonetics::CV, {"ゐ", "ヰ", "wi", "ви"}}, // obsolete
     {Phonetics::CV, {"ゑ", "ヱ", "we", "вэ"}}, // obsolete
     {Phonetics::CV, {"を", "ヲ", "wo", "во"}}
};





////////// diphtongs //////////
#ifdef USE_ARRAY
static Symbol Column2_K_D[] =
#else
static SymVec Column2_K_D =
#endif
{
     {Phonetics::CVD, {"きゃ", "キャ", "kya", "кя"}},
     {Phonetics::CVD, {"きゅ", "キュ", "kyu", "кю"}},
     {Phonetics::CVD, {"きょ", "キョ", "kyo", "кё"}}
};

#ifdef USE_ARRAY
static Symbol Column2_G_D[] =
#else
static SymVec Column2_G_D =
#endif
{
     {Phonetics::CVD, {"ぎゃ", "ギャ", "gya", "гя"}},
     {Phonetics::CVD, {"ぎゅ", "ギュ", "gyu", "гю"}},
     {Phonetics::CVD, {"ぎょ", "ギョ", "gyo", "гё"}}
};

#ifdef USE_ARRAY
static Symbol Column3_S_D[] =
#else
static SymVec Column3_S_D =
#endif
{
     {Phonetics::CVD, {"しゃ", "シャ", "sha", "ша"}}, // fix
     {Phonetics::CVD, {"しゅ", "シュ", "shu", "шю"}},
     {Phonetics::CVD, {"しょ", "ショ", "sho", "шё"}}
};

#ifdef USE_ARRAY
static Symbol Column3_Z_D[] =
#else
static SymVec Column3_Z_D =
#endif
{
     {Phonetics::CVD, {"じゃ", "ジャ", "ja", "джя"}},
     {Phonetics::CVD, {"じゅ", "ジュ", "ju", "джю"}},
     {Phonetics::CVD, {"じょ", "ジョ", "jo", "джо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_T_D[] =
#else
static SymVec Column4_T_D =
#endif
{
     {Phonetics::CVD, {"ちゃ", "チャ", "cha", "ча"}}, // fix
     {Phonetics::CVD, {"ちゅ", "チュ", "chu", "чю"}},
     {Phonetics::CVD, {"ちょ", "チョ", "cho", "чо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_D_D[] =
#else
static SymVec Column4_D_D =
#endif
{
     {Phonetics::CVD, {"ぢゃ", "ヂャ", "dja", "ча"}}, // fix
     {Phonetics::CVD, {"ぢゅ", "ヂュ", "dju", "чю"}},
     {Phonetics::CVD, {"ぢょ", "ヂョ", "djo", "чо"}}
};

#ifdef USE_ARRAY
static Symbol Column5_N_D[] =
#else
static SymVec Column5_N_D =
#endif
{
     {Phonetics::CVD, {"にゃ", "ニャ", "nya", "ня"}},
     {Phonetics::CVD, {"にゅ", "ニュ", "nyu", "ню"}},
     {Phonetics::CVD, {"にょ", "ニョ", "nyo", "нё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_H_D[] =
#else
static SymVec Column6_H_D =
#endif
{
     {Phonetics::CVD, {"ひゃ", "ヒャ", "hya", "хя"}},
     {Phonetics::CVD, {"ひゅ", "ヒュ", "hyu", "хю"}},
     {Phonetics::CVD, {"ひょ", "ヒョ", "hyo", "хё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_B_D[] =
#else
static SymVec Column6_B_D =
#endif
{
     {Phonetics::CVD, {"びゃ", "ビャ", "bya", "бя"}},
     {Phonetics::CVD, {"びゅ", "ビュ", "byu", "бю"}},
     {Phonetics::CVD, {"びょ", "ビョ", "byo", "бё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_P_D[] =
#else
static SymVec Column6_P_D =
#endif
{
     {Phonetics::CVD, {"ぴゃ", "ピャ", "pya", "пя"}},
     {Phonetics::CVD, {"ぴゅ", "ピュ", "pyu", "пю"}},
     {Phonetics::CVD, {"ぴょ", "ピョ", "pyo", "пё"}}
};

#ifdef USE_ARRAY
static Symbol Column7_M_D[] =
#else
static SymVec Column7_M_D =
#endif
{
     {Phonetics::CVD, {"みゃ", "ミャ", "mya", "мя"}},
     {Phonetics::CVD, {"みゅ", "ミュ", "myu", "мю"}},
     {Phonetics::CVD, {"みょ", "ミョ", "myo", "мё"}}
};

#ifdef USE_ARRAY
static Symbol Column9_R_D[] =
#else
static SymVec Column9_R_D =
#endif
{
     {Phonetics::CVD, {"りゃ", "リャ", "rya", "ря"}},
     {Phonetics::CVD, {"りゅ", "リュ", "ryu", "рю"}},
     {Phonetics::CVD, {"りょ", "リョ", "ryo", "рё"}}
};

#ifdef USE_ARRAY
static Symbol Column10_W_D[] =
#else
static SymVec Column10_W_D =
#endif
{   // is it even exist?
     {Phonetics::CV, {"ゐゃ", "ヰャ", "wya", "вя"}},
     {Phonetics::CV, {"ゐゅ", "ヰュ", "wyu", "вю"}},
     {Phonetics::CV, {"ゐょ", "ヰョ", "wyo", "вё"}}
};
