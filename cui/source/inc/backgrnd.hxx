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
#ifndef INCLUDED_CUI_SOURCE_INC_BACKGRND_HXX
#define INCLUDED_CUI_SOURCE_INC_BACKGRND_HXX

#include <vcl/group.hxx>
#include <svtools/stdctrl.hxx>
#include <vcl/graph.hxx>
#include <svx/SvxColorValueSet.hxx>
#include <svx/dlgctrl.hxx>
#include <editeng/brushitem.hxx>

class BackgroundPreviewImpl;
class SvxOpenGraphicDialog;
struct SvxBackgroundTable_Impl;
struct SvxBackgroundPara_Impl;
struct SvxBackgroundPage_Impl;
class SvxBrushItem;

/** class SvxBackgroundTabPage --------------------------------------------

    [Description]
    With this TabPage a Brush (e. g. for a frame's background color)
    can be set.
    [Items]
    <SvxBrushItem>:     <SID_ATTR_BRUSH>;
*/

class SvxBackgroundTabPage : public SvxTabPage
{
    using TabPage::DeactivatePage;
    friend class VclPtr<SvxBackgroundTabPage>;
    static const sal_uInt16 pPageRanges[];
public:
    static VclPtr<SfxTabPage>  Create( vcl::Window* pParent, const SfxItemSet* rAttrSet );
    // returns the area of the which-values
    static const sal_uInt16* GetRanges() { return pPageRanges; }

    virtual bool        FillItemSet( SfxItemSet* rSet ) SAL_OVERRIDE;
    virtual void        Reset( const SfxItemSet* rSet ) SAL_OVERRIDE;
    virtual void        FillUserData() SAL_OVERRIDE;
    virtual void        PointChanged( vcl::Window* pWindow, RECT_POINT eRP ) SAL_OVERRIDE;

    /// Shift-ListBox activation
    void                ShowSelector();
    /// for the Writer (cells/rows/tables)
    void                ShowTblControl();
    /// for the Writer (paragraph/characters)
    void                ShowParaControl(bool bCharOnly = false);

    virtual void        PageCreated(const SfxAllItemSet& aSet) SAL_OVERRIDE;
protected:
    virtual sfxpg       DeactivatePage( SfxItemSet* pSet = 0 ) SAL_OVERRIDE;

private:
    SvxBackgroundTabPage( vcl::Window* pParent, const SfxItemSet& rCoreSet );
    virtual ~SvxBackgroundTabPage();
    virtual void dispose() SAL_OVERRIDE;

    VclPtr<VclContainer>           m_pAsGrid;
    VclPtr<FixedText>              m_pSelectTxt;
    VclPtr<ListBox>                m_pLbSelect;
    VclPtr<FixedText>              m_pTblDesc;
    VclPtr<ListBox>                m_pTblLBox;
    VclPtr<ListBox>                m_pParaLBox;

    VclPtr<FixedText>              m_pBackGroundColorLabelFT;
    VclPtr<VclFrame>               m_pBackGroundColorFrame;
    VclPtr<SvxColorValueSet>       m_pBackgroundColorSet;
    VclPtr<BackgroundPreviewImpl>  m_pPreviewWin1;

    VclPtr<CheckBox>               m_pBtnPreview;

    // Background Bitmap ----------------------------------
    VclPtr<VclContainer>           m_pBitmapContainer;
    VclPtr<VclContainer>           m_pFileFrame;
    VclPtr<PushButton>             m_pBtnBrowse;
    VclPtr<CheckBox>               m_pBtnLink;
    VclPtr<FixedText>              m_pFtUnlinked;
    VclPtr<FixedText>              m_pFtFile;

    VclPtr<VclContainer>           m_pTypeFrame;
    VclPtr<RadioButton>            m_pBtnPosition;
    VclPtr<RadioButton>            m_pBtnArea;
    VclPtr<RadioButton>            m_pBtnTile;
    VclPtr<SvxRectCtl>             m_pWndPosition;

    VclPtr<BackgroundPreviewImpl>  m_pPreviewWin2;

    // DDListBox for Writer -------------------------------

    Color       aBgdColor;
    sal_uInt16      nHtmlMode;
    bool        bAllowShowSelector  : 1;
    bool        bIsGraphicValid     : 1;
    bool        bLinkOnly           : 1;
    Graphic     aBgdGraphic;
    OUString    aBgdGraphicPath;
    OUString    aBgdGraphicFilter;

    SvxBackgroundPage_Impl* pPageImpl;
    SvxOpenGraphicDialog* pImportDlg;

    SvxBackgroundTable_Impl*    pTableBck_Impl;///< Items for Sw-Table must be corrected
    SvxBackgroundPara_Impl* pParaBck_Impl;///< also for the paragraph style

    void                FillColorValueSets_Impl();
    void                ShowColorUI_Impl();
    void                HideColorUI_Impl();
    void                ShowBitmapUI_Impl();
    void                HideBitmapUI_Impl();
    bool                LoadLinkedGraphic_Impl();
    void                RaiseLoadError_Impl();
    void                SetGraphicPosition_Impl( SvxGraphicPosition ePos );
    SvxGraphicPosition  GetGraphicPosition_Impl();
    void                FillControls_Impl(const SvxBrushItem& rBgdAttr,
                                            const OUString& rUserData);
    bool                FillItemSetWithWallpaperItem( SfxItemSet& rCoreSet, sal_uInt16 nSlot);
    void                ResetFromWallpaperItem( const SfxItemSet& rSet );

    DECL_LINK_TYPED( LoadIdleHdl_Impl, Idle*, void );
    DECL_LINK(SelectHdl_Impl, void *);
    DECL_LINK(BrowseHdl_Impl, void *);
    DECL_LINK( RadioClickHdl_Impl, RadioButton* );
    DECL_LINK( FileClickHdl_Impl, CheckBox* );
    DECL_LINK(BackgroundColorHdl_Impl, void *);
    DECL_LINK( TblDestinationHdl_Impl, ListBox* );
    DECL_LINK( ParaDestinationHdl_Impl, ListBox* );
};

#endif // INCLUDED_CUI_SOURCE_INC_BACKGRND_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
