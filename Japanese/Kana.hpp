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

//union SymbolFlags {
//    using sz = uint32_t;

//    sz raw{0};
//    struct {
//        sz row : 8;
//    };
//};

struct Symbol {
    using sz = uint32_t;

    struct {
        sz row : 4;
        sz col : 4;
    } flags;
    Phonetics   phonetics;
    QStringList text;
};
using SymVec = std::vector<Symbol>;
using PhoVec = std::vector<Phonetics>;

static const QChar DoubleVowelSign = ':';
//static const Symbol LongVowel       = {Phonetics::V, {"ー"}}
static Symbol   SmallTsu    = {{0, 0}, Phonetics::SmallTSU, {"っ", "ッ", "", ""}};
static Symbol   NN          = {{0, 0}, Phonetics::N, {"ん", "ン", "nn", "нн"}};

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
    {{1, 1}, Phonetics::V, {"あ", "ア", "a", "а"}},
    {{2, 1}, Phonetics::V, {"い", "イ", "i", "и"}},
    {{3, 1}, Phonetics::V, {"う", "ウ", "u", "у"}},
    {{4, 1}, Phonetics::V, {"え", "エ", "e", "э"}},
    {{5, 1}, Phonetics::V, {"お", "オ", "o", "о"}}
};

#ifdef USE_ARRAY
static Symbol Column2_K[] =
#else
static SymVec Column2_K =
#endif
{
    {{1, 2}, Phonetics::CV, {"か", "カ", "ka", "ка"}},
    {{2, 2}, Phonetics::CV, {"き", "キ", "ki", "ки"}},
    {{3, 2}, Phonetics::CV, {"く", "ク", "ku", "ку"}},
    {{4, 2}, Phonetics::CV, {"け", "ケ", "ke", "кэ"}},
    {{5, 2}, Phonetics::CV, {"こ", "コ", "ko", "ко"}}
};

#ifdef USE_ARRAY
static Symbol Column2_G[] =
#else
static SymVec Column2_G =
#endif
{
    {{1, 2}, Phonetics::CV, {"が", "ガ", "ga", "га"}},
    {{2, 2}, Phonetics::CV, {"ぎ", "ギ", "gi", "ги"}},
    {{3, 2}, Phonetics::CV, {"ぐ", "グ", "gu", "гу"}},
    {{4, 2}, Phonetics::CV, {"げ", "ゲ", "ge", "гэ"}},
    {{5, 2}, Phonetics::CV, {"ご", "ゴ", "go", "го"}}
};

#ifdef USE_ARRAY
static Symbol Column3_S[] =
#else
static SymVec Column3_S =
#endif
{
    {{1, 3}, Phonetics::CV, {"さ", "サ", "sa", "са"}},
    {{2, 3}, Phonetics::CV, {"し", "シ", shi_eng, shi_rus}},
    {{3, 3}, Phonetics::CV, {"す", "ス", "su", "су"}},
    {{4, 3}, Phonetics::CV, {"せ", "セ", "se", "сэ"}},
    {{5, 3}, Phonetics::CV, {"そ", "ソ", "so", "со"}}
};

#ifdef USE_ARRAY
static Symbol Column3_Z[] =
#else
static SymVec Column3_Z =
#endif
{
    {{1, 3}, Phonetics::CV, {"ざ", "ザ", "za", "дза"}},
    {{2, 3}, Phonetics::CV, {"じ", "ジ", "ji", "дзи"}},
    {{3, 3}, Phonetics::CV, {"ず", "ズ", "zu", "дзу"}},
    {{4, 3}, Phonetics::CV, {"ぜ", "ズ", "ze", "дзэ"}},
    {{5, 3}, Phonetics::CV, {"ぞ", "ゾ", "zo", "дзо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_T[] =
#else
static SymVec Column4_T =
#endif
{
    {{1, 4}, Phonetics::CV, {"た", "タ", "ta", "та"}},
    {{2, 4}, Phonetics::CV, {"ち", "チ", chi_eng, chi_rus}},
    {{3, 4}, Phonetics::CV, {"つ", "ツ", tsu_eng, tsu_rus}},
    {{4, 4}, Phonetics::CV, {"て", "テ", "te", "тэ"}},
    {{5, 4}, Phonetics::CV, {"と", "テ", "to", "то"}}
};

#ifdef USE_ARRAY
static Symbol Column4_D[] =
#else
static SymVec Column4_D =
#endif
{
    {{1, 4}, Phonetics::CV, {"だ", "ダ", "da", "да"}},
    {{2, 4}, Phonetics::CV, {"ぢ", "ヂ", di_eng, di_rus}},
    {{3, 4}, Phonetics::CV, {"づ", "ヅ", du_eng, du_rus}},
    {{4, 4}, Phonetics::CV, {"で", "デ", "de", "дэ"}},
    {{5, 4}, Phonetics::CV, {"ど", "ド", "do", "до"}}
};

#ifdef USE_ARRAY
static Symbol Column5_N[] =
#else
static SymVec Column5_N =
#endif
{
    {{1, 5}, Phonetics::CV, {"な", "ナ", "na", "на"}},
    {{2, 5}, Phonetics::CV, {"に", "ニ", "ni", "ни"}},
    {{3, 5}, Phonetics::CV, {"ぬ", "ヌ", "nu", "ну"}},
    {{4, 5}, Phonetics::CV, {"ね", "ネ", "ne", "нэ"}},
    {{5, 5}, Phonetics::CV, {"の", "ノ", "no", "но"}}
};

#ifdef USE_ARRAY
static Symbol Column6_H[] =
#else
static SymVec Column6_H =
#endif
{
    {{1, 6}, Phonetics::CV, {"は", "ハ", "ha", "ха"}},
    {{2, 6}, Phonetics::CV, {"ひ", "ヒ", "hi", "хи"}},
    {{3, 6}, Phonetics::CV, {"ふ", "フ", "fu", "фу"}},
    {{4, 6}, Phonetics::CV, {"へ", "ヘ", "he", "хэ"}},
    {{5, 6}, Phonetics::CV, {"ほ", "ホ", "ho", "хо"}}
};

#ifdef USE_ARRAY
static Symbol Column6_B[] =
#else
static SymVec Column6_B =
#endif
{
    {{1, 6}, Phonetics::CV, {"ば", "バ", "ba", "ба"}},
    {{2, 6}, Phonetics::CV, {"び", "ビ", "bi", "би"}},
    {{3, 6}, Phonetics::CV, {"ぶ", "ブ", "bu", "бу"}},
    {{4, 6}, Phonetics::CV, {"べ", "ボ", "be", "бэ"}},
    {{5, 6}, Phonetics::CV, {"ぼ", "ベ", "bo", "бо"}}
};

#ifdef USE_ARRAY
static Symbol Column6_P[] =
#else
static SymVec Column6_P =
#endif
{
    {{1, 6}, Phonetics::CV, {"ぱ", "パ", "pa", "па"}},
    {{2, 6}, Phonetics::CV, {"ぴ", "ピ", "pi", "пи"}},
    {{3, 6}, Phonetics::CV, {"ぷ", "プ", "pu", "пу"}},
    {{4, 6}, Phonetics::CV, {"ぺ", "ポ", "pe", "пэ"}},
    {{5, 6}, Phonetics::CV, {"ぽ", "ペ", "po", "по"}}
};

#ifdef USE_ARRAY
static Symbol Column7_M[] =
#else
static SymVec Column7_M =
#endif
{
     {{1, 7}, Phonetics::CV, {"ま", "マ", "ma", "ма"}},
     {{2, 7}, Phonetics::CV, {"み", "ミ", "mi", "ми"}},
     {{3, 7}, Phonetics::CV, {"む", "ム", "mu", "му"}},
     {{4, 7}, Phonetics::CV, {"め", "メ", "me", "мэ"}},
     {{5, 7}, Phonetics::CV, {"も", "モ", "mo", "мо"}}
};

#ifdef USE_ARRAY
static Symbol Column8_Y[] =
#else
static SymVec Column8_Y =
#endif
{
     {{1, 8}, Phonetics::D, {"や", "ヤ", "ya", "я"}},
     {{3, 8}, Phonetics::D, {"ゆ", "ユ", "yu", "ю"}},
     {{5, 8}, Phonetics::D, {"よ", "ヨ", "yo", "ё"}}
};

#ifdef USE_ARRAY
static Symbol Column9_R[] =
#else
static SymVec Column9_R =
#endif
{
     {{1, 9}, Phonetics::CV, {"ら", "ラ", "ra", "ра"}},
     {{2, 9}, Phonetics::CV, {"り", "リ", "ri", "ри"}},
     {{3, 9}, Phonetics::CV, {"る", "ル", "ru", "ру"}},
     {{4, 9}, Phonetics::CV, {"れ", "レ", "re", "рэ"}},
     {{5, 9}, Phonetics::CV, {"ろ", "ロ", "ro", "ро"}}
};

#ifdef USE_ARRAY
static Symbol Column10_W[] =
#else
static SymVec Column10_W =
#endif
{
     {{1, 10}, Phonetics::CV, {"わ", "ワ", "wa", "ва"}},
     {{2, 10}, Phonetics::CV, {"ゐ", "ヰ", "wi", "ви"}}, // obsolete
     {{4, 10}, Phonetics::CV, {"ゑ", "ヱ", "we", "вэ"}}, // obsolete
     {{5, 10}, Phonetics::CV, {"を", "ヲ", "wo", "во"}}
};





////////// diphtongs //////////
#ifdef USE_ARRAY
static Symbol Column2_K_D[] =
#else
static SymVec Column2_K_D =
#endif
{
     {{2, 2}, Phonetics::CVD, {"きゃ", "キャ", "kya", "кя"}},
     {{2, 2}, Phonetics::CVD, {"きゅ", "キュ", "kyu", "кю"}},
     {{2, 2}, Phonetics::CVD, {"きょ", "キョ", "kyo", "кё"}}
};

#ifdef USE_ARRAY
static Symbol Column2_G_D[] =
#else
static SymVec Column2_G_D =
#endif
{
     {{2, 2}, Phonetics::CVD, {"ぎゃ", "ギャ", "gya", "гя"}},
     {{2, 2}, Phonetics::CVD, {"ぎゅ", "ギュ", "gyu", "гю"}},
     {{2, 2}, Phonetics::CVD, {"ぎょ", "ギョ", "gyo", "гё"}}
};

#ifdef USE_ARRAY
static Symbol Column3_S_D[] =
#else
static SymVec Column3_S_D =
#endif
{
     {{2, 3}, Phonetics::CVD, {"しゃ", "シャ", "sha", "ша"}}, // fix
     {{2, 3}, Phonetics::CVD, {"しゅ", "シュ", "shu", "шю"}},
     {{2, 3}, Phonetics::CVD, {"しょ", "ショ", "sho", "шё"}}
};

#ifdef USE_ARRAY
static Symbol Column3_Z_D[] =
#else
static SymVec Column3_Z_D =
#endif
{
     {{2, 3}, Phonetics::CVD, {"じゃ", "ジャ", "ja", "джя"}},
     {{2, 3}, Phonetics::CVD, {"じゅ", "ジュ", "ju", "джю"}},
     {{2, 3}, Phonetics::CVD, {"じょ", "ジョ", "jo", "джо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_T_D[] =
#else
static SymVec Column4_T_D =
#endif
{
     {{2, 4}, Phonetics::CVD, {"ちゃ", "チャ", "cha", "ча"}}, // fix
     {{2, 4}, Phonetics::CVD, {"ちゅ", "チュ", "chu", "чю"}},
     {{2, 4}, Phonetics::CVD, {"ちょ", "チョ", "cho", "чо"}}
};

#ifdef USE_ARRAY
static Symbol Column4_D_D[] =
#else
static SymVec Column4_D_D =
#endif
{
     {{2, 4}, Phonetics::CVD, {"ぢゃ", "ヂャ", "dja", "ча"}}, // fix
     {{2, 4}, Phonetics::CVD, {"ぢゅ", "ヂュ", "dju", "чю"}},
     {{2, 4}, Phonetics::CVD, {"ぢょ", "ヂョ", "djo", "чо"}}
};

#ifdef USE_ARRAY
static Symbol Column5_N_D[] =
#else
static SymVec Column5_N_D =
#endif
{
     {{2, 5}, Phonetics::CVD, {"にゃ", "ニャ", "nya", "ня"}},
     {{2, 5}, Phonetics::CVD, {"にゅ", "ニュ", "nyu", "ню"}},
     {{2, 5}, Phonetics::CVD, {"にょ", "ニョ", "nyo", "нё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_H_D[] =
#else
static SymVec Column6_H_D =
#endif
{
     {{2, 6}, Phonetics::CVD, {"ひゃ", "ヒャ", "hya", "хя"}},
     {{2, 6}, Phonetics::CVD, {"ひゅ", "ヒュ", "hyu", "хю"}},
     {{2, 6}, Phonetics::CVD, {"ひょ", "ヒョ", "hyo", "хё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_B_D[] =
#else
static SymVec Column6_B_D =
#endif
{
     {{2, 6}, Phonetics::CVD, {"びゃ", "ビャ", "bya", "бя"}},
     {{2, 6}, Phonetics::CVD, {"びゅ", "ビュ", "byu", "бю"}},
     {{2, 6}, Phonetics::CVD, {"びょ", "ビョ", "byo", "бё"}}
};

#ifdef USE_ARRAY
static Symbol Column6_P_D[] =
#else
static SymVec Column6_P_D =
#endif
{
     {{2, 6}, Phonetics::CVD, {"ぴゃ", "ピャ", "pya", "пя"}},
     {{2, 6}, Phonetics::CVD, {"ぴゅ", "ピュ", "pyu", "пю"}},
     {{2, 6}, Phonetics::CVD, {"ぴょ", "ピョ", "pyo", "пё"}}
};

#ifdef USE_ARRAY
static Symbol Column7_M_D[] =
#else
static SymVec Column7_M_D =
#endif
{
     {{2, 7}, Phonetics::CVD, {"みゃ", "ミャ", "mya", "мя"}},
     {{2, 7}, Phonetics::CVD, {"みゅ", "ミュ", "myu", "мю"}},
     {{2, 7}, Phonetics::CVD, {"みょ", "ミョ", "myo", "мё"}}
};

#ifdef USE_ARRAY
static Symbol Column9_R_D[] =
#else
static SymVec Column9_R_D =
#endif
{
     {{2, 9}, Phonetics::CVD, {"りゃ", "リャ", "rya", "ря"}},
     {{2, 9}, Phonetics::CVD, {"りゅ", "リュ", "ryu", "рю"}},
     {{2, 9}, Phonetics::CVD, {"りょ", "リョ", "ryo", "рё"}}
};

#ifdef USE_ARRAY
static Symbol Column10_W_D[] =
#else
static SymVec Column10_W_D =
#endif
{   // is it even exist?
     {{2, 10}, Phonetics::CV, {"ゐゃ", "ヰャ", "wya", "вя"}},
     {{2, 10}, Phonetics::CV, {"ゐゅ", "ヰュ", "wyu", "вю"}},
     {{2, 10}, Phonetics::CV, {"ゐょ", "ヰョ", "wyo", "вё"}}
};
