///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB.                                  //
//                                                                               //
// Thanks to Sven Reifegerste: http://www.zorc.breitbandkatze.de/crc.html        //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef CRC_H_
#define CRC_H_

namespace DSDcc
{

class CRC
{
public:
    CRC(unsigned long _polynom,
            int _order,
            unsigned long _crcinit,
            unsigned long _crcxor,
            int _direct = 1,
            int _refin = 0,
            int _refout = 0);

    ~CRC();

    int getOrder() const
    {
        return m_order;
    }
    unsigned long getPolynom() const
    {
        return m_poly;
    }
    unsigned long getCRCInit() const
    {
        return m_crcinit;
    }
    unsigned long getCRCXOR() const
    {
        return m_crcxor;
    }
    int getRefin() const
    {
        return m_refin;
    }
    int getRefout() const
    {
        return m_refout;
    }
    unsigned long getCRCInitDirect()
    {
        return m_crcinit_direct;
    }
    unsigned long getCRCInitNonDirect()
    {
        return m_crcinit_nondirect;
    }

    /** normal lookup table algorithm with augmented zero bytes.
    * only usable with polynom orders of 8, 16, 24 or 32.
    */
    unsigned long crctable(unsigned char* p, unsigned long len);

    /** fast lookup table algorithm without augmented zero bytes, e.g. used in pkzip.
    * only usable with polynom orders of 8, 16, 24 or 32.
    */
    unsigned long crctablefast(unsigned char* p, unsigned long len);

    /** bit by bit algorithm with augmented zero bytes.
    * does not use lookup table, suited for polynom orders between 1...32.
    */
    unsigned long crcbitbybit(unsigned char* p, unsigned long len);

    /** fast bit by bit algorithm without augmented zero bytes.
    * does not use lookup table, suited for polynom orders between 1...32.
    */
    unsigned long crcbitbybitfast(unsigned char* p, unsigned long len);

    static const unsigned long PolyCCITT16;

private:
    unsigned long reflect(unsigned long crc, int bitnum);
    void generate_crc_table();
    void init();

    int           m_order;   //!< CRC order (# bits)
    unsigned long m_poly; //!< Polynomial in hex
    int           m_direct;  //!< algorithm: 1 = direct, no augmented zero bits
    unsigned long m_crcinit; //!< Shift register is initialized with this value
    unsigned long m_crcxor;  //!< At the end bits are XORed with this value
    int           m_refin;   //!< data byte is reflected before processing (UART)
    int           m_refout;  //!< CRC will be reflected before XOR

    unsigned long m_crcmask;
    unsigned long m_crchighbit;
    unsigned long m_crcinit_direct;
    unsigned long m_crcinit_nondirect;
    unsigned long m_crctab[256];
};

} // namespace DSDcc

#endif /* CRC_H_ */
