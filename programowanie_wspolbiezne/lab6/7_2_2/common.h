#define INPUT_QUEUE_NAME "/InputQueue"
#define OUTPUT_QUEUE_NAME "/OutputQueue"

struct SectionInput
{
    int pocz;  // początek przedzialu
    int kon;   // koniec przedzialu
    int numer; // Kolejny numer odcinka
};

struct SectionResult
{
    int ile;   // Obliczony wynik dla przedziału
    int numer; // Kolejny numer odcinka
};

extern int errno;