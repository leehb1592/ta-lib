/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  112400 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #using <mscorlib.dll>
/* Generated */    #include "Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (TA_INTERNAL_ERROR)
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::TRANGE_Lookback( /* Generated */ void )
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_TRANGE_Lookback( /* Generated */ void )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */

   return 1;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_TRANGE - True Range
 * 
 * Input  = High, Low, Close
 * Output = double
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::TRANGE( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     double       inHigh __gc [],
/* Generated */                                     double       inLow __gc [],
/* Generated */                                     double       inClose __gc [],
/* Generated */                                     [OutAttribute]Int32 *outBegIdx,
/* Generated */                                     [OutAttribute]Int32 *outNbElement,
/* Generated */                                     double        outReal __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_TRANGE( int    startIdx,
/* Generated */                       int    endIdx,
/* Generated */                       const double inHigh[],
/* Generated */                       const double inLow[],
/* Generated */                       const double inClose[],
/* Generated */                       int          *outBegIdx,
/* Generated */                       int          *outNbElement,
/* Generated */                       double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   int today, outIdx;
   double val2, val3, greatest;
   double tempCY, tempLT, tempHT;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh||!inLow||!inClose)
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outReal == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* True Range is the greatest of the following: 
    *
    *  val1 = distance from today's high to today's low.
    *  val2 = distance from yesterday's close to today's high.
    *  val3 = distance from yesterday's close to today's low.   
    *
    * Some books and software makes the first TR value to be
    * the (high - low) of the first bar. This function instead
    * ignore the first price bar, and only output starting at the
    * second price bar are valid. This is done for avoiding
    * inconsistency.
    */

   /* Move up the start index if there is not
    * enough initial data.
    * Always one price bar gets consumed.
    */
   if( startIdx < 1 )
      startIdx = 1;      

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outBegIdx = 0;
      *outNbElement = 0;
      return TA_SUCCESS;
   }

   outIdx = 0;
   today = startIdx;
   while( today <= endIdx )
   {

      /* Find the greatest of the 3 values. */
      tempLT = inLow[today];
      tempHT = inHigh[today];
      tempCY = inClose[today-1];
      greatest = tempHT - tempLT; /* val1 */

      val2 = fabs( tempCY - tempHT );
      if( val2 > greatest )
         greatest = val2;

      val3 = fabs( tempCY - tempLT  );
      if( val3 > greatest )
         greatest = val3;

      outReal[outIdx++] = greatest;
      today++;
   }

   *outNbElement = outIdx;
   *outBegIdx    = startIdx; 

   return TA_SUCCESS;
}

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::TRANGE( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     float        inHigh __gc [],
/* Generated */                                     float        inLow __gc [],
/* Generated */                                     float        inClose __gc [],
/* Generated */                                     [OutAttribute]Int32 *outBegIdx,
/* Generated */                                     [OutAttribute]Int32 *outNbElement,
/* Generated */                                     double        outReal __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_TRANGE( int    startIdx,
/* Generated */                         int    endIdx,
/* Generated */                         const float  inHigh[],
/* Generated */                         const float  inLow[],
/* Generated */                         const float  inClose[],
/* Generated */                         int          *outBegIdx,
/* Generated */                         int          *outNbElement,
/* Generated */                         double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    int today, outIdx;
/* Generated */    double val2, val3, greatest;
/* Generated */    double tempCY, tempLT, tempHT;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if(!inHigh||!inLow||!inClose)
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outReal == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    if( startIdx < 1 )
/* Generated */       startIdx = 1;      
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       *outBegIdx = 0;
/* Generated */       *outNbElement = 0;
/* Generated */       return TA_SUCCESS;
/* Generated */    }
/* Generated */    outIdx = 0;
/* Generated */    today = startIdx;
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */       tempLT = inLow[today];
/* Generated */       tempHT = inHigh[today];
/* Generated */       tempCY = inClose[today-1];
/* Generated */       greatest = tempHT - tempLT; 
/* Generated */       val2 = fabs( tempCY - tempHT );
/* Generated */       if( val2 > greatest )
/* Generated */          greatest = val2;
/* Generated */       val3 = fabs( tempCY - tempLT  );
/* Generated */       if( val3 > greatest )
/* Generated */          greatest = val3;
/* Generated */       outReal[outIdx++] = greatest;
/* Generated */       today++;
/* Generated */    }
/* Generated */    *outNbElement = outIdx;
/* Generated */    *outBegIdx    = startIdx; 
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

