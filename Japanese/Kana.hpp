#pragma once
#include <QStringList>
#include <vector>
#include <array>


enum Phonetics : uint32_t {
    C = 0,
    V,
    D,
    CV,
    CVD,
    SmallTSU,
    N
};

enum Flags : uint32_t {
    NONE        = 0,

    // kana type
    Original    = 1 << 8,
    Special     = 1 << 9,
    Extra1      = 1 << 10,

    // columns and rows
    Col1        = 1 << 11,
    Col2        = 1 << 12,
    Col3        = 1 << 13,
    Col4        = 1 << 14,
    Col5        = 1 << 15,
    Col6        = 1 << 16,
    Col7        = 1 << 17,
    Col8        = 1 << 18,
    Col9        = 1 << 19,
    Col10       = 1 << 20,
    Row1        = 1 << 21,
    Row2        = 1 << 22,
    Row3        = 1 << 23,
    Row4        = 1 << 24,
    Row5        = 1 << 25,

    // other
    Rare            = 1 << 26,
    Obsolete        = 1 << 27,
    ExtraPhonetics  = 1 << 28

    //Test        = 0x0000000100000000
};

enum SymbolEnum {
    Hiragana = 0,
    Katakana,
    PhoneticsENG,
    PhoneticsRUS
};

struct Symbol {
    QStringList     text;
    Phonetics       phonetics;
    Flags           flag;
};
using SymVec = std::vector<Symbol>;
using PhoVec = std::vector<Phonetics>;

static Symbol   DoubleVowelSign = {{"", "", ":", ":"},{},{}};
//static const Symbol LongVowel       = {Phonetics::V, {"ー"}}
static Symbol   SmallTsu    = {{"っ", "ッ", "|", "|"},        Phonetics::SmallTSU, Flags::NONE};
static Symbol   NN          = {{"ん", "ン", "nn", "нн"},    Phonetics::N, Flags::NONE};
static Symbol   MM          = {{"ん", "ン", "mm", "мм"},    Phonetics::N, Flags::NONE};

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






////////// Original //////////

static SymVec KanaVowels =
{
    {{"あ", "ア", "a","а"},       Phonetics::V, Flags(Col1|Row1|Original)},          ///< Vowels
    {{"い", "イ", "i", "и"},      Phonetics::V, Flags(Col1|Row2|Original)},
    {{"う", "ウ", "u", "у"},      Phonetics::V, Flags(Col1|Row3|Original)},
    {{"え", "エ", "e", "э"},      Phonetics::V, Flags(Col1|Row4|Original)},
    {{"お", "オ", "o", "о"},      Phonetics::V, Flags(Col1|Row5|Original)}
};

static SymVec KanaK =
{
    {{"か", "カ", "ka", "ка"},    Phonetics::CV, Flags(Col2|Row1|Original)},          ///< K
    {{"き", "キ", "ki", "ки"},    Phonetics::CV, Flags(Col2|Row2|Original)},
    {{"く", "ク", "ku", "ку"},    Phonetics::CV, Flags(Col2|Row3|Original)},
    {{"け", "ケ", "ke", "кэ"},    Phonetics::CV, Flags(Col2|Row4|Original)},
    {{"こ", "コ", "ko", "ко"},    Phonetics::CV, Flags(Col2|Row5|Original)}
};

static SymVec KanaS =
{
    {{"さ", "サ", "sa", "са"},        Phonetics::CV, Flags(Col3|Row1|Original)},          ///< S
    {{"し", "シ", shi_eng, shi_rus},  Phonetics::CV, Flags(Col3|Row2|Original | ExtraPhonetics)},
    {{"す", "ス", "su", "су"},        Phonetics::CV, Flags(Col3|Row3|Original)},
    {{"せ", "セ", "se", "сэ"},        Phonetics::CV, Flags(Col3|Row4|Original)},
    {{"そ", "ソ", "so", "со"},        Phonetics::CV, Flags(Col3|Row5|Original)}
};

static SymVec KanaT =
{
    {{"た", "タ", "ta", "та"},        Phonetics::CV, Flags(Col4|Row1|Original)},          ///< T
    {{"ち", "チ", chi_eng, chi_rus},  Phonetics::CV, Flags(Col4|Row2|Original | ExtraPhonetics)},
    {{"つ", "ツ", tsu_eng, tsu_rus},  Phonetics::CV, Flags(Col4|Row3|Original | ExtraPhonetics)},
    {{"て", "テ", "te", "тэ"},        Phonetics::CV, Flags(Col4|Row4|Original)},
    {{"と", "テ", "to", "то"},        Phonetics::CV, Flags(Col4|Row5|Original)}
};

static SymVec KanaN =
{
    {{"な", "ナ", "na", "на"},    Phonetics::CV, Flags(Col5|Row1|Original)},          ///< N
    {{"に", "ニ", "ni", "ни"},    Phonetics::CV, Flags(Col5|Row2|Original)},
    {{"ぬ", "ヌ", "nu", "ну"},    Phonetics::CV, Flags(Col5|Row3|Original)},
    {{"ね", "ネ", "ne", "нэ"},    Phonetics::CV, Flags(Col5|Row4|Original)},
    {{"の", "ノ", "no", "но"},    Phonetics::CV, Flags(Col5|Row5|Original)}
};

static SymVec KanaH =
{
    {{"は", "ハ", "ha", "ха"},    Phonetics::CV, Flags(Col6|Row1|Original)},          ///< H
    {{"ひ", "ヒ", "hi", "хи"},    Phonetics::CV, Flags(Col6|Row2|Original)},
    {{"ふ", "フ", "fu", "фу"},    Phonetics::CV, Flags(Col6|Row3|Original)},
    {{"へ", "ヘ", "he", "хэ"},    Phonetics::CV, Flags(Col6|Row4|Original)},
    {{"ほ", "ホ", "ho", "хо"},    Phonetics::CV, Flags(Col6|Row5|Original)}
};

static SymVec KanaM =
{
    {{"ま", "マ", "ma", "ма"},    Phonetics::CV, Flags(Col7|Row1|Original)},          ///< M
    {{"み", "ミ", "mi", "ми"},    Phonetics::CV, Flags(Col7|Row2|Original)},
    {{"む", "ム", "mu", "му"},    Phonetics::CV, Flags(Col7|Row3|Original)},
    {{"め", "メ", "me", "мэ"},    Phonetics::CV, Flags(Col7|Row4|Original)},
    {{"も", "モ", "mo", "мо"},    Phonetics::CV, Flags(Col7|Row5|Original)}
};

static SymVec KanaY =
{
    {{"や", "ヤ", "ya", "я"},     Phonetics::D, Flags(Col8|Row1|Original)},          ///< Y
    {{"ゆ", "ユ", "yu", "ю"},     Phonetics::D, Flags(Col8|Row3|Original)},
    {{"よ", "ヨ", "yo", "ё"},     Phonetics::D, Flags(Col8|Row5|Original)}
};

static SymVec KanaR =
{
    {{"ら", "ラ", "ra", "ра"},    Phonetics::CV, Flags(Col9|Row1|Original)},          ///< R
    {{"り", "リ", "ri", "ри"},    Phonetics::CV, Flags(Col9|Row2|Original)},
    {{"る", "ル", "ru", "ру"},    Phonetics::CV, Flags(Col9|Row3|Original)},
    {{"れ", "レ", "re", "рэ"},    Phonetics::CV, Flags(Col9|Row4|Original)},
    {{"ろ", "ロ", "ro", "ро"},    Phonetics::CV, Flags(Col9|Row5|Original)}
};

static SymVec KanaW =
{
    {{"わ", "ワ", "wa", "ва"},    Phonetics::CV, Flags(Col10|Row1|Original)},          ///< W
    {{"ゐ", "ヰ", "wi", "ви"},    Phonetics::CV, Flags(Col10|Row2|Original | Obsolete)},
    {{"ゑ", "ヱ", "we", "вэ"},    Phonetics::CV, Flags(Col10|Row4|Original | Obsolete)},
    {{"を", "ヲ", "wo", "во"},    Phonetics::CV, Flags(Col10|Row5|Original)}
};





////////// Specials //////////

static SymVec KanaSpecialG =
{
    {{"が", "ガ", "ga", "га"},    Phonetics::CV, Flags(Col2|Row1|Special)},           ///< G
    {{"ぎ", "ギ", "gi", "ги"},    Phonetics::CV, Flags(Col2|Row2|Special)},
    {{"ぐ", "グ", "gu", "гу"},    Phonetics::CV, Flags(Col2|Row3|Special)},
    {{"げ", "ゲ", "ge", "гэ"},    Phonetics::CV, Flags(Col2|Row4|Special)},
    {{"ご", "ゴ", "go", "го"},    Phonetics::CV, Flags(Col2|Row5|Special)}
};

static SymVec KanaSpecialZ =
{
    {{"ざ", "ザ", "za", "дза"},   Phonetics::CV, Flags(Col3|Row1|Special)},           ///< Z
    {{"じ", "ジ", "ji", "дзи"},   Phonetics::CV, Flags(Col3|Row2|Special)},
    {{"ず", "ズ", "zu", "дзу"},   Phonetics::CV, Flags(Col3|Row3|Special)},
    {{"ぜ", "ズ", "ze", "дзэ"},   Phonetics::CV, Flags(Col3|Row4|Special)},
    {{"ぞ", "ゾ", "zo", "дзо"},   Phonetics::CV, Flags(Col3|Row5|Special)}
};

static SymVec KanaSpecialD =
{
    {{"だ", "ダ", "da", "да"},        Phonetics::CV, Flags(Col4|Row1|Special)},           ///< D
    {{"ぢ", "ヂ", di_eng, di_rus},    Phonetics::CV, Flags(Col4|Row2|Special | Rare | ExtraPhonetics)},
    {{"づ", "ヅ", du_eng, du_rus},    Phonetics::CV, Flags(Col4|Row3|Special | Rare | ExtraPhonetics)},
    {{"で", "デ", "de", "дэ"},        Phonetics::CV, Flags(Col4|Row4|Special)},
    {{"ど", "ド", "do", "до"},        Phonetics::CV, Flags(Col4|Row5|Special)}
};

static SymVec KanaSpecialB =
{
    {{"ば", "バ", "ba", "ба"},    Phonetics::CV, Flags(Col6|Row1|Special)},           ///< B
    {{"び", "ビ", "bi", "би"},    Phonetics::CV, Flags(Col6|Row2|Special)},
    {{"ぶ", "ブ", "bu", "бу"},    Phonetics::CV, Flags(Col6|Row3|Special)},
    {{"べ", "ボ", "be", "бэ"},    Phonetics::CV, Flags(Col6|Row4|Special)},
    {{"ぼ", "ベ", "bo", "бо"},    Phonetics::CV, Flags(Col6|Row5|Special)}
};

static SymVec KanaSpecialP =
{
    {{"ぱ", "パ", "pa", "па"},    Phonetics::CV, Flags(Col6|Row1|Special)},           ///< P
    {{"ぴ", "ピ", "pi", "пи"},    Phonetics::CV, Flags(Col6|Row2|Special)},
    {{"ぷ", "プ", "pu", "пу"},    Phonetics::CV, Flags(Col6|Row3|Special)},
    {{"ぺ", "ポ", "pe", "пэ"},    Phonetics::CV, Flags(Col6|Row4|Special)},
    {{"ぽ", "ペ", "po", "по"},    Phonetics::CV, Flags(Col6|Row5|Special)}
};





////////// Extra //////////

static SymVec KanaExtraK =
{
    {{"きゃ", "キャ", "kya", "кя"},     Phonetics::CVD, Flags(Col2|Row1|Extra1)},         ///< K
    {{"きゅ", "キュ", "kyu", "кю"},     Phonetics::CVD, Flags(Col2|Row3|Extra1)},
    {{"きょ", "キョ", "kyo", "кё"},     Phonetics::CVD, Flags(Col2|Row5|Extra1)}
};

static SymVec KanaExtraG =
{
    {{"ぎゃ", "ギャ", "gya", "гя"},     Phonetics::CVD, Flags(Col2|Row1|Extra1)},         ///< G
    {{"ぎゅ", "ギュ", "gyu", "гю"},     Phonetics::CVD, Flags(Col2|Row3|Extra1)},
    {{"ぎょ", "ギョ", "gyo", "гё"},     Phonetics::CVD, Flags(Col2|Row5|Extra1)}
};

static SymVec KanaExtraS =
{
    {{"しゃ", "シャ", "sha", "ша"},     Phonetics::CVD, Flags(Col3|Row1|Extra1)},         ///< S(SH) // fix phonetics
    {{"しゅ", "シュ", "shu", "шю"},     Phonetics::CVD, Flags(Col3|Row3|Extra1)},
    {{"しょ", "ショ", "sho", "шё"},     Phonetics::CVD, Flags(Col3|Row5|Extra1)}
};

static SymVec KanaExtraZ =
{
    {{"じゃ", "ジャ", "ja", "джя"},     Phonetics::CVD, Flags(Col3|Row1|Extra1)},         ///< Z(J)
    {{"じゅ", "ジュ", "ju", "джю"},     Phonetics::CVD, Flags(Col3|Row3|Extra1)},
    {{"じょ", "ジョ", "jo", "джо"},     Phonetics::CVD, Flags(Col3|Row5|Extra1)}
};

static SymVec KanaExtraT =
{
    {{"ちゃ", "チャ", "cha", "ча"},     Phonetics::CVD, Flags(Col4|Row1|Extra1)},         ///< T(CH) // fix phonetics
    {{"ちゅ", "チュ", "chu", "чю"},     Phonetics::CVD, Flags(Col4|Row3|Extra1)},
    {{"ちょ", "チョ", "cho", "чо"},     Phonetics::CVD, Flags(Col4|Row5|Extra1)}
};

static SymVec KanaExtraD =
{
    {{"ぢゃ", "ヂャ", "dja", "ча"},     Phonetics::CVD, Flags(Col4|Row1|Extra1)},         ///< D(DJ) // fix phonetics
    {{"ぢゅ", "ヂュ", "dju", "чю"},     Phonetics::CVD, Flags(Col4|Row3|Extra1)},
    {{"ぢょ", "ヂョ", "djo", "чо"},     Phonetics::CVD, Flags(Col4|Row5|Extra1)}
};

static SymVec KanaExtraN =
{
    {{"にゃ", "ニャ", "nya", "ня"},     Phonetics::CVD, Flags(Col5|Row1|Extra1)},         ///< N
    {{"にゅ", "ニュ", "nyu", "ню"},     Phonetics::CVD, Flags(Col5|Row3|Extra1)},
    {{"にょ", "ニョ", "nyo", "нё"},     Phonetics::CVD, Flags(Col5|Row5|Extra1)}
};

static SymVec KanaExtraH =
{
    {{"ひゃ", "ヒャ", "hya", "хя"},     Phonetics::CVD, Flags(Col6|Row1|Extra1)},         ///< H
    {{"ひゅ", "ヒュ", "hyu", "хю"},     Phonetics::CVD, Flags(Col6|Row3|Extra1)},
    {{"ひょ", "ヒョ", "hyo", "хё"},     Phonetics::CVD, Flags(Col6|Row5|Extra1)}
};

static SymVec KanaExtraB =
{
    {{"びゃ", "ビャ", "bya", "бя"},     Phonetics::CVD, Flags(Col6|Row1|Extra1)},         ///< B
    {{"びゅ", "ビュ", "byu", "бю"},     Phonetics::CVD, Flags(Col6|Row3|Extra1)},
    {{"びょ", "ビョ", "byo", "бё"},     Phonetics::CVD, Flags(Col6|Row5|Extra1)}
};

static SymVec KanaExtraP =
{
    {{"ぴゃ", "ピャ", "pya", "пя"},     Phonetics::CVD, Flags(Col6|Row1|Extra1)},         ///< P
    {{"ぴゅ", "ピュ", "pyu", "пю"},     Phonetics::CVD, Flags(Col6|Row3|Extra1)},
    {{"ぴょ", "ピョ", "pyo", "пё"},     Phonetics::CVD, Flags(Col6|Row5|Extra1)}
};

static SymVec KanaExtraM =
{
    {{"みゃ", "ミャ", "mya", "мя"},     Phonetics::CVD, Flags(Col7|Row1|Extra1)},         ///< M
    {{"みゅ", "ミュ", "myu", "мю"},     Phonetics::CVD, Flags(Col7|Row3|Extra1)},
    {{"みょ", "ミョ", "myo", "мё"},     Phonetics::CVD, Flags(Col7|Row5|Extra1)}
};

static SymVec KanaExtraR =
{
    {{"りゃ", "リャ", "rya", "ря"},     Phonetics::CVD, Flags(Col9|Row1|Extra1)},         ///< R
    {{"りゅ", "リュ", "ryu", "рю"},     Phonetics::CVD, Flags(Col9|Row3|Extra1)},
    {{"りょ", "リョ", "ryo", "рё"},     Phonetics::CVD, Flags(Col9|Row5|Extra1)}
};

static SymVec KanaExtraW =
{
    {{"ゐゃ", "ヰャ", "wya", "вя"},     Phonetics::CVD, Flags(Col10|Row1|Extra1)},        ///< W is it even exist?
    {{"ゐゅ", "ヰュ", "wyu", "вю"},     Phonetics::CVD, Flags(Col10|Row3|Extra1)},
    {{"ゐょ", "ヰョ", "wyo", "вё"},     Phonetics::CVD, Flags(Col10|Row5|Extra1)}
};





////////// For Alphabet //////////

static SymVec KanaSmallY =
{
    {{"ゃ", "ャ", "", ""},{},{}},
    {{"ゅ", "ュ", "", ""},{},{}},
    {{"ょ", "ョ", "", ""},{},{}}
};
