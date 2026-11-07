// ===== Member 2: validateEncodedData =====
/* Checks that an encoded barcode string is valid before we draw it.
 * Input    : encoded -> string made of '1' (black bar) and '0' (white space)
 * Returns  : true if valid, false if invalid
 */
bool InputValidator::validateEncodedData(const std::string& encoded)
{
    if (encoded.empty())
    {
        return false;
    }
    int length = (int)encoded.length();
    if (length > MAX_ENCODED_LEN)
    {
        return false;
    }
    bool hasBlackBar = false;
    for (int i = 0; i < length; i++)
    {
        char c = encoded[i];
        if (c != '0' && c != '1')        //only 0 and 1 is allowed
        {
            return false;
        }
        if (c == '1')
        {
            hasBlackBar = true;
        }
    }
    return hasBlackBar;
}