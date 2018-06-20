// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry               
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
// 
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution 
//    may be used to endorse or promote products derived from this software 
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS. 
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING 
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// --------------------------------------------------------------------------
// $Maintainer: Timo Sachsenberg$
// $Authors: Timo Sachsenberg $
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/ClassTest.h>
#include <OpenMS/test_config.h>

///////////////////////////
#include <OpenMS/KERNEL/MSSpectrum.h>
#include <OpenMS/KERNEL/MSChromatogram.h>
#include <OpenMS/KERNEL/SpectrumHelper.h>
///////////////////////////

using namespace OpenMS;
using namespace std;

START_TEST(SpectrumHelper, "$Id$")

START_SECTION((MSSpectrum::FloatDataArrays::iterator getDataArrayByName(MSSpectrum::FloatDataArrays& a, const String& name)))
	MSSpectrum ds;
	MSSpectrum::FloatDataArray float_array;
        float_array.push_back(56);  
        float_array.push_back(201); 
        float_array.push_back(31);  
        float_array.push_back(201); 
        float_array.push_back(201);  
	
        ds.getFloatDataArrays() = std::vector<MSSpectrum::FloatDataArray>(3, float_array);
	ds.getFloatDataArrays()[0].setName("f1");
	ds.getFloatDataArrays()[1].setName("f2");
	ds.getFloatDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f2") == ds.getFloatDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "NOT_THERE") == ds.getFloatDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f1") - ds.getFloatDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f2") - ds.getFloatDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f3") - ds.getFloatDataArrays().begin(), 2);

        // test const version
        const MSSpectrum::FloatDataArrays cfa(ds.getFloatDataArrays());
        TEST_EQUAL(getDataArrayByName(cfa, "f2") == cfa.end(), false);
        TEST_EQUAL(getDataArrayByName(cfa, "f1") - cfa.begin(), 0);
        TEST_EQUAL(getDataArrayByName(cfa, "NOT_THERE") == cfa.end(), true);

END_SECTION

START_SECTION((MSSpectrum::StringDataArrays::iterator getDataArrayByName(MSSpectrum::StringDataArrays& a, const String& name)))
	MSSpectrum ds;
	MSSpectrum::StringDataArray string_array;
        string_array.push_back("56");  
        string_array.push_back("201"); 
        string_array.push_back("31");  
        string_array.push_back("201"); 
        string_array.push_back("201");  
	ds.getStringDataArrays() = std::vector<MSSpectrum::StringDataArray>(3, string_array);
	ds.getStringDataArrays()[0].setName("f1");
	ds.getStringDataArrays()[1].setName("f2");
	ds.getStringDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f2") == ds.getStringDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "NOT_THERE") == ds.getStringDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f1") - ds.getStringDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f2") - ds.getStringDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f3") - ds.getStringDataArrays().begin(), 2);
END_SECTION

START_SECTION((MSSpectrum::IntegerDataArrays::iterator getDataArrayByName(MSSpectrum::IntegerDataArrays& a, const String& name)))
	MSSpectrum ds;
	MSSpectrum::IntegerDataArray int_array;
        int_array.push_back(56);  
        int_array.push_back(201); 
        int_array.push_back(31);  
        int_array.push_back(201); 
        int_array.push_back(201);  

	ds.getIntegerDataArrays() = std::vector<MSSpectrum::IntegerDataArray>(3, int_array);
	ds.getIntegerDataArrays()[0].setName("f1");
	ds.getIntegerDataArrays()[1].setName("f2");
	ds.getIntegerDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f2") == ds.getIntegerDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "NOT_THERE") == ds.getIntegerDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f1") - ds.getIntegerDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f2") - ds.getIntegerDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f3") - ds.getIntegerDataArrays().begin(), 2);
END_SECTION

START_SECTION((MSChromatogram::FloatDataArrays::iterator getDataArrayByName(const MSChromatogram::FloatDataArrays& a, const String& name)))
	MSChromatogram ds;
	MSChromatogram::FloatDataArray float_array;
        float_array.push_back(56);  
        float_array.push_back(201); 
        float_array.push_back(31);  
        float_array.push_back(201); 
        float_array.push_back(201);  
	
        ds.getFloatDataArrays() = std::vector<MSChromatogram::FloatDataArray>(3, float_array);
	ds.getFloatDataArrays()[0].setName("f1");
	ds.getFloatDataArrays()[1].setName("f2");
	ds.getFloatDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f2") == ds.getFloatDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "NOT_THERE") == ds.getFloatDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f1") - ds.getFloatDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f2") - ds.getFloatDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getFloatDataArrays(), "f3") - ds.getFloatDataArrays().begin(), 2);
END_SECTION

START_SECTION((MSChromatogram::StringDataArrays::iterator getDataArrayByName(MSChromatogram::StringDataArrays& a, const String& name)))
	MSChromatogram ds;
	MSChromatogram::StringDataArray string_array;
        string_array.push_back("56");  
        string_array.push_back("201"); 
        string_array.push_back("31");  
        string_array.push_back("201"); 
        string_array.push_back("201");  
	ds.getStringDataArrays() = std::vector<MSChromatogram::StringDataArray>(3, string_array);
	ds.getStringDataArrays()[0].setName("f1");
	ds.getStringDataArrays()[1].setName("f2");
	ds.getStringDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f2") == ds.getStringDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "NOT_THERE") == ds.getStringDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f1") - ds.getStringDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f2") - ds.getStringDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getStringDataArrays(), "f3") - ds.getStringDataArrays().begin(), 2);
END_SECTION

START_SECTION((MSChromatogram::IntegerDataArrays::iterator getDataArrayByName(MSChromatogram::IntegerDataArrays& a, const String& name)))
	MSChromatogram ds;
	MSChromatogram::IntegerDataArray int_array;
        int_array.push_back(56);  
        int_array.push_back(201); 
        int_array.push_back(31);  
        int_array.push_back(201); 
        int_array.push_back(201);  

	ds.getIntegerDataArrays() = std::vector<MSChromatogram::IntegerDataArray>(3, int_array);
	ds.getIntegerDataArrays()[0].setName("f1");
	ds.getIntegerDataArrays()[1].setName("f2");
	ds.getIntegerDataArrays()[2].setName("f3");

        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f2") == ds.getIntegerDataArrays().end(), false);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "NOT_THERE") == ds.getIntegerDataArrays().end(), true);

        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f1") - ds.getIntegerDataArrays().begin(), 0);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f2") - ds.getIntegerDataArrays().begin(), 1);
        TEST_EQUAL(getDataArrayByName(ds.getIntegerDataArrays(), "f3") - ds.getIntegerDataArrays().begin(), 2);
END_SECTION

START_SECTION(void slicePeakContainer(PeakContainerT& p, const double pos_start, const double pos_end))
{
  MSSpectrum s;
  MSChromatogram c;

  for (Size i = 5; i < 15; ++i) // RTs: [5 14]
  {
    s.push_back(Peak1D(i, 0));
    c.push_back(ChromatogramPeak(i, 0));
  }

  MSSpectrum s1 = s;
  slicePeakContainer(s1, 3, 6); // start rt (3) is lower than the minimum (5) within the spectrum
  TEST_EQUAL(s1.size(), 2)
  TEST_REAL_SIMILAR(s1[0].getPos(), 5)
  TEST_REAL_SIMILAR(s1[1].getPos(), 6)

  MSSpectrum s2 = s;
  slicePeakContainer(s2, 0, 4); // no peak within the requested range
  TEST_EQUAL(s2.size(), 0)

  MSChromatogram c1 = c;
  slicePeakContainer(c1, 12, 16); // end rt (16) is higher than the maximum (14) within the chromatogram
  TEST_EQUAL(c1.size(), 3)
  TEST_REAL_SIMILAR(c1[0].getPos(), 12)
  TEST_REAL_SIMILAR(c1[1].getPos(), 13)
  TEST_REAL_SIMILAR(c1[2].getPos(), 14)

  MSChromatogram c2 = c;
  slicePeakContainer(c2, 9, 12); // all within the range
  TEST_EQUAL(c2.size(), 4)
  TEST_REAL_SIMILAR(c2[0].getPos(), 9)
  TEST_REAL_SIMILAR(c2[1].getPos(), 10)
  TEST_REAL_SIMILAR(c2[2].getPos(), 11)
  TEST_REAL_SIMILAR(c2[3].getPos(), 12)

  MSSpectrum s_empty;
  slicePeakContainer(s_empty, 9, 12);
  TEST_EQUAL(s_empty.size(), 0)
}
END_SECTION

START_SECTION(void rebaseIntensities(PeakContainerT& p))
{
  MSSpectrum s;
  MSChromatogram c;

  for (Int i = -5; i < 5; ++i) // Intensities: [-5 4]
  {
    s.push_back(Peak1D(i + 5, i));
    c.push_back(ChromatogramPeak(i + 5, i));
  }

  rebaseIntensities(s);
  TEST_REAL_SIMILAR(s[0].getIntensity(), 0)
  TEST_REAL_SIMILAR(s[1].getIntensity(), 1)
  TEST_REAL_SIMILAR(s[9].getIntensity(), 9)

  // Now `s` does not have any negative intensity. It won't be modified
  rebaseIntensities(s);
  TEST_REAL_SIMILAR(s[0].getIntensity(), 0)
  TEST_REAL_SIMILAR(s[1].getIntensity(), 1)
  TEST_REAL_SIMILAR(s[9].getIntensity(), 9)

  rebaseIntensities(c);
  TEST_REAL_SIMILAR(c[0].getIntensity(), 0)
  TEST_REAL_SIMILAR(c[1].getIntensity(), 1)
  TEST_REAL_SIMILAR(c[9].getIntensity(), 9)

  // Now `c` does not have any negative intensity. It won't be modified
  rebaseIntensities(c);
  TEST_REAL_SIMILAR(c[0].getIntensity(), 0)
  TEST_REAL_SIMILAR(c[1].getIntensity(), 1)
  TEST_REAL_SIMILAR(c[9].getIntensity(), 9)

  MSChromatogram c_empty;
  rebaseIntensities(c_empty);
  TEST_EQUAL(c_empty.size(), 0)
}
END_SECTION

END_TEST

