/*
 * File    : BarcodeDecoder.cpp
 * Purpose : Pattern decoding and verification (Members 4 and 5)
 */
#include "BarcodeDecoder.h"
#include "BarcodeEncoder.h"
#include <iostream>
#include <string>
using namespace std;
 // ===== Member 4: decodeDigitPattern =====
char BarcodeDecoder::decodeDigitPattern(const std::string& pattern)
{
    // TODO (Member 4)
    return '?';
}



// ===== Member 4: verifyDecodedResult =====
bool BarcodeDecoder::verifyDecodedResult(const std::string& decoded)
{
    // TODO (Member 4)
    return false;
}



// ===== Member 5: decodeScannedPattern =====

    static int gcdInt(int a, int b)
    {
        while (b != 0)
        {
            int t = a % b;
            a = b;
            b = t;
        }

        return a;
    }


    static string normalizePattern(const string & raw)
    {
        int first = -1;
        int last = -1;

        // Find first and last black module
        for (int i = 0; i < raw.length(); i++)
        {
            if (raw[i] == '1')
            {
                if (first == -1)
                    first = i;

                last = i;
            }
        }

        if (first == -1)
            return "";

        string p = raw.substr(first, last - first + 1);

        int g = 0;
        int i = 0;

        // Find GCD of run lengths
        while (i < p.length())
        {
            int j = i;

            while (j < p.length() && p[j] == p[i])
                j++;

            g = gcdInt(g, j - i);

            i = j;
        }

        if (g <= 1)
            return p;

        // Normalize run lengths
        string out = "";

        i = 0;

        while (i < p.length())
        {
            int j = i;

            while (j < p.length() && p[j] == p[i])
                j++;

            out.append((j - i) / g, p[i]);

            i = j;
        }

        return out;
    }


    string BarcodeDecoder::decodeScannedPattern(const string & scanned)
    {
        const int SYMBOL_LEN = 11;
        const int STOP_LEN = 13;
        const int TOTAL_LEN = 5 * SYMBOL_LEN + STOP_LEN;

        if (scanned.empty())
        {
            cout << "Decode error: No pattern received.\n";
            return "";
        }

        // Validate binary input
        for (int i = 0; i < scanned.length(); i++)
        {
            if (scanned[i] != '0' && scanned[i] != '1')
            {
                cout << "Decode error: Invalid binary pattern.\n";
                return "";
            }
        }

        string pattern = normalizePattern(scanned);

        if (pattern.empty())
        {
            cout << "Decode error: No black bars found.\n";
            return "";
        }

        if (pattern.length() != TOTAL_LEN)
        {
            cout << "Decode error: Invalid barcode length.\n";
            return "";
        }

        // Check Start C
        if (pattern.substr(0, SYMBOL_LEN) !=
            BarcodeEncoder::getDigitPattern(BarcodeEncoder::START_C))
        {
            cout << "Decode error: Start C not found.\n";
            return "";
        }

        // Check Stop
        if (pattern.substr(5 * SYMBOL_LEN, STOP_LEN) !=
            BarcodeEncoder::getDigitPattern(BarcodeEncoder::STOP))
        {
            cout << "Decode error: Stop pattern not found.\n";
            return "";
        }

        int values[4];

        // Decode three digit pairs and checksum
        for (int s = 0; s < 4; s++)
        {
            string chunk = pattern.substr((s + 1) * SYMBOL_LEN, SYMBOL_LEN);

            values[s] = -1;

            int maxValue = (s == 3) ? 102 : 99;

            for (int v = 0; v <= maxValue; v++)
            {
                if (BarcodeEncoder::getDigitPattern(v) == chunk)
                {
                    values[s] = v;
                    break;
                }
            }

            if (values[s] == -1)
            {
                cout << "Decode error: Invalid symbol "
                    << s + 1 << ".\n";
                return "";
            }
        }

        // Verify checksum
        int expected = BarcodeEncoder::calculateSum(
            values[0], values[1], values[2]);

        if (values[3] != expected)
        {
            cout << "Decode error: Checksum mismatch.\n";
            return "";
        }

        // Convert pairs into six digits
        string result = "";

        for (int i = 0; i < 3; i++)
        {
            result += char('0' + values[i] / 10);
            result += char('0' + values[i] % 10);
        }

        return result;
    }
