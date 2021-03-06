/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_SC_INC_RANGEUTL_HXX
#define INCLUDED_SC_INC_RANGEUTL_HXX

#include "address.hxx"
#include "rangenam.hxx"
#include "dbdata.hxx"
#include "scdllapi.h"

#include <com/sun/star/table/CellAddress.hpp>
#include <com/sun/star/table/CellRangeAddress.hpp>
#include <com/sun/star/uno/Sequence.hxx>

class ScArea;
class ScDocument;
class ScRange;
class ScRangeName;
class ScRangeList;
class ScDBCollection;

enum RutlNameScope { RUTL_NONE=0, RUTL_NAMES, RUTL_DBASE };

class SC_DLLPUBLIC ScRangeUtil
{
public:
                ScRangeUtil()  {}
                ~ScRangeUtil() {}

    static bool MakeArea        ( const OUString&     rAreaStr,
                                  ScArea&           rArea,
                                  ScDocument*       pDoc,
                                  SCTAB         nTab,
                                  ScAddress::Details const & rDetails = ScAddress::detailsOOOa1 );

    static void CutPosString    ( const OUString&     theAreaStr,
                                  OUString&           thePosStr );

    static bool IsAbsTabArea    ( const OUString&   rAreaStr,
                                  ScDocument*       pDoc,
                                  ScArea***         pppAreas    = 0,
                                  sal_uInt16*       pAreaCount  = 0,
                                  bool              bAcceptCellRef = false,
                                  ScAddress::Details const & rDetails = ScAddress::detailsOOOa1 );

    static bool IsAbsArea       ( const OUString& rAreaStr,
                                  ScDocument*   pDoc,
                                  SCTAB     nTab,
                                  OUString*     pCompleteStr = 0,
                                  ScRefAddress* pStartPos    = 0,
                                  ScRefAddress* pEndPos      = 0,
                                  ScAddress::Details const & rDetails = ScAddress::detailsOOOa1 );

    static bool IsAbsPos        ( const OUString& rPosStr,
                                  ScDocument*   pDoc,
                                  SCTAB     nTab,
                                  OUString*       pCompleteStr = 0,
                                  ScRefAddress* pPosTripel   = 0,
                                  ScAddress::Details const & rDetails = ScAddress::detailsOOOa1 );

    static bool MakeRangeFromName( const OUString& rName,
                                    ScDocument*     pDoc,
                                    SCTAB           nCurTab,
                                    ScRange&        rRange,
                                  RutlNameScope eScope=RUTL_NAMES,
                                  ScAddress::Details const & rDetails = ScAddress::detailsOOOa1 );
};

class SC_DLLPUBLIC ScRangeStringConverter
{
public:

/// helper methods
    static void         AssignString(
                            OUString& rString,
                            const OUString& rNewStr,
                            bool bAppendStr,
                            sal_Unicode cSeparator = ' ');

    static sal_Int32    IndexOf(
                            const OUString& rString,
                            sal_Unicode cSearchChar,
                            sal_Int32 nOffset,
                            sal_Unicode cQuote = '\'');

    static sal_Int32    IndexOfDifferent(
                            const OUString& rString,
                            sal_Unicode cSearchChar,
                            sal_Int32 nOffset );

    static sal_Int32    GetTokenCount(
                            const OUString& rString,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');

    static void         GetTokenByOffset(
                            OUString& rToken,
                            const OUString& rString,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');

    static void         AppendTableName(
                            OUStringBuffer& rBuf,
                            const OUString& rTabName,
                            sal_Unicode cQuote = '\'');

/// String to Range core
    static bool     GetAddressFromString(
                            ScAddress& rAddress,
                            const OUString& rAddressStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');
    static bool     GetRangeFromString(
                            ScRange& rRange,
                            const OUString& rRangeStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');
    static bool     GetRangeListFromString(
                            ScRangeList& rRangeList,
                            const OUString& rRangeListStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');

    static bool     GetAreaFromString(
                            ScArea& rArea,
                            const OUString& rRangeStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');

/// String to Range API
    static bool     GetAddressFromString(
                            ::com::sun::star::table::CellAddress& rAddress,
                            const OUString& rAddressStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');
    static bool     GetRangeFromString(
                            ::com::sun::star::table::CellRangeAddress& rRange,
                            const OUString& rRangeStr,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Int32& nOffset,
                            sal_Unicode cSeparator = ' ',
                            sal_Unicode cQuote = '\'');

/// Range to String core
    static void         GetStringFromAddress(
                            OUString& rString,
                            const ScAddress& rAddress,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            bool bAppendStr = false,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void         GetStringFromRange(
                            OUString& rString,
                            const ScRange& rRange,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            bool bAppendStr = false,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void         GetStringFromRangeList(
                            OUString& rString,
                            const ScRangeList* pRangeList,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D));

    static void         GetStringFromArea(
                            OUString& rString,
                            const ScArea& rArea,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            bool bAppendStr = false,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );

/// Range to String API
    static void         GetStringFromAddress(
                            OUString& rString,
                            const ::com::sun::star::table::CellAddress& rAddress,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            bool bAppendStr = false,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void         GetStringFromRange(
                            OUString& rString,
                            const ::com::sun::star::table::CellRangeAddress& rRange,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            bool bAppendStr = false,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void         GetStringFromRangeList(
                            OUString& rString,
                            const ::com::sun::star::uno::Sequence< ::com::sun::star::table::CellRangeAddress >& rRangeSeq,
                            const ScDocument* pDocument,
                            formula::FormulaGrammar::AddressConvention eConv,
                            sal_Unicode cSeparator = ' ',
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );

/// XML Range to Calc Range
    static void         GetStringFromXMLRangeString(
                            OUString& rString,
                            const OUString& rXMLRange,
                            ScDocument* pDoc );

/// String to RangeData core
    static ScRangeData* GetRangeDataFromString(const OUString& rString, const SCTAB nTab, const ScDocument* pDoc);
};

class ScArea
{
public:
            ScArea( SCTAB tab      = 0,
                    SCCOL colStart = 0,
                    SCROW rowStart = 0,
                    SCCOL colEnd   = 0,
                    SCROW rowEnd   = 0 );

            ScArea( const ScArea& r );

    ScArea& operator=   ( const ScArea& r );
    bool    operator==  ( const ScArea& r ) const;
    bool    operator!=  ( const ScArea& r ) const  { return !( operator==(r) ); }

public:
    SCTAB nTab;
    SCCOL nColStart;
    SCROW nRowStart;
    SCCOL nColEnd;
    SCROW nRowEnd;
};

///  @return areas with reference and all db-areas

class SC_DLLPUBLIC ScAreaNameIterator
{
private:
    ScRangeName*    pRangeName;
    ScDBCollection* pDBCollection;
    ScRangeName::const_iterator maRNPos;
    ScRangeName::const_iterator maRNEnd;
    ScDBCollection::NamedDBs::const_iterator maDBPos;
    ScDBCollection::NamedDBs::const_iterator maDBEnd;
    bool            bFirstPass;

public:
            ScAreaNameIterator( ScDocument* pDoc );
            ~ScAreaNameIterator() {}

    bool Next( OUString& rName, ScRange& rRange );
    bool WasDBName() const { return !bFirstPass; }
};

#endif // INCLUDED_SC_INC_RANGEUTL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
