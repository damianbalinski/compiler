/*
 * TERMINAL SYMBOL/TOKEN KIND (z wielkich liter)
 * odpowiada pojedynczemu tokenowi, tokeny sa reprezentowane przez
 * wartosci calkowite, funkcja yylex zwraca kolejne kody tokenow
 */

/*
 * RODZAJE TERMINALI
 * TERMINAL ZNAKOWY (pojedyczny znak)
 * - kod odpowiada wartosci numerycznej znaku
 * - nie musi byc zadeklarowany
 * - czasami wymaga zrzutowania wartosci char na unsigned char
 *
 * TERMINAL LANCUCHOWY (wiele znakow, bison only)
 * - nie musi byc zadeklarowany
 *
 * TERMINAL NAZWANY 
 * - bison generuje macro, ktorego nazwa odpowiada nazwie tokena
 * - musi byc zadeklarowany, np. w %token
 */

/*
 * ZAREZERWOWANE TERMINALE
 * NAZWA - WAROSC - OPIS
 *       - 0      - end of file
 *                - znak nowej linii
 * error - 256    - blacd, redukcja do tego nieterminala nastepuje
                    gdy na stoaiw pojawia sie ciag tokenow nieposiadajacy
                    odpowiedniego dopasowania w regulach, yylexer nigdy
                    nie zwraca tej wartosci
 */