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
#ifndef INCLUDED_ACCESSIBILITY_INC_ACCESSIBILITY_STANDARD_VCLXACCESSIBLETOOLBOXITEM_HXX
#define INCLUDED_ACCESSIBILITY_INC_ACCESSIBILITY_STANDARD_VCLXACCESSIBLETOOLBOXITEM_HXX

#include <com/sun/star/accessibility/XAccessible.hpp>
#include <com/sun/star/accessibility/XAccessibleAction.hpp>
#include <com/sun/star/accessibility/XAccessibleComponent.hpp>
#include <com/sun/star/accessibility/XAccessibleContext.hpp>
#include <com/sun/star/accessibility/XAccessibleStateSet.hpp>
#include <com/sun/star/accessibility/XAccessibleText.hpp>
#include <com/sun/star/accessibility/XAccessibleEventBroadcaster.hpp>
#include <com/sun/star/accessibility/XAccessibleValue.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <cppuhelper/implbase4.hxx>
#include <comphelper/accessibletexthelper.hxx>
#include <vcl/vclptr.hxx>

class ToolBox;

typedef ::comphelper::OAccessibleTextHelper AccessibleTextHelper_BASE;
typedef ::cppu::ImplHelper4 < ::com::sun::star::accessibility::XAccessible,
                              ::com::sun::star::accessibility::XAccessibleAction,
                              ::com::sun::star::accessibility::XAccessibleValue,
                              ::com::sun::star::lang::XServiceInfo > VCLXAccessibleToolBoxItem_BASE;

class VCLExternalSolarLock;

class VCLXAccessibleToolBoxItem : public AccessibleTextHelper_BASE,
                                  public VCLXAccessibleToolBoxItem_BASE
{
private:
    OUString                m_sOldName;
    VclPtr<ToolBox>         m_pToolBox;
    VCLExternalSolarLock*   m_pExternalLock;
    sal_Int32               m_nIndexInParent;
    sal_Int16               m_nRole;
    sal_uInt16              m_nItemId;
    bool                    m_bHasFocus;
    bool                    m_bIsChecked;
    bool                    m_bIndeterminate;

    ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >    m_xChild;

public:
    inline sal_Int32    getIndexInParent() const                    { return m_nIndexInParent; }
    inline void         setIndexInParent( sal_Int32 _nNewIndex )    { m_nIndexInParent = _nNewIndex; }

protected:
    virtual ~VCLXAccessibleToolBoxItem();

    virtual void SAL_CALL                   disposing() SAL_OVERRIDE;

    /// implements the calculation of the bounding rectangle
    virtual ::com::sun::star::awt::Rectangle implGetBounds(  ) throw (::com::sun::star::uno::RuntimeException) SAL_OVERRIDE;

    // OCommonAccessibleText
    virtual OUString                                    implGetText() SAL_OVERRIDE;
    virtual ::com::sun::star::lang::Locale              implGetLocale() SAL_OVERRIDE;
    virtual void                                        implGetSelection( sal_Int32& nStartIndex, sal_Int32& nEndIndex ) SAL_OVERRIDE;

    OUString GetText( bool _bAsName );

public:
    VCLXAccessibleToolBoxItem( ToolBox* _pToolBox, sal_Int32 _nPos );

    void                SetFocus( bool _bFocus );
    inline bool         HasFocus() const { return m_bHasFocus; }
    void                SetChecked( bool _bCheck );
    inline bool         IsChecked() const { return m_bIsChecked; }
    void                SetIndeterminate( bool _bIndeterminate );
    inline bool         IsIndeterminate() const { return m_bIndeterminate; }
    inline void         ReleaseToolBox() { m_pToolBox = NULL; }
    void                NameChanged();
    void                SetChild( const ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >& _xChild );
    ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >
                        GetChild() const { return m_xChild; }
    void                NotifyChildEvent( const ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >& _xChild, bool _bShow );

    void                ToggleEnableState();

    // XInterface
    DECLARE_XINTERFACE( )
    DECLARE_XTYPEPROVIDER( )

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL supportsService( const OUString& rServiceName ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames() throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessible
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext > SAL_CALL getAccessibleContext(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleContext
    virtual sal_Int32 SAL_CALL getAccessibleChildCount(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL getAccessibleChild( sal_Int32 i ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL getAccessibleParent(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Int32 SAL_CALL getAccessibleIndexInParent(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Int16 SAL_CALL getAccessibleRole(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual OUString SAL_CALL getAccessibleDescription(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual OUString SAL_CALL getAccessibleName(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleRelationSet > SAL_CALL getAccessibleRelationSet(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleStateSet > SAL_CALL getAccessibleStateSet(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleText
    virtual sal_Int32 SAL_CALL getCaretPosition() throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL setCaretPosition( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL getCharacterAttributes( sal_Int32 nIndex, const ::com::sun::star::uno::Sequence< OUString >& aRequestedAttributes ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::awt::Rectangle SAL_CALL getCharacterBounds( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Int32 SAL_CALL getIndexAtPoint( const ::com::sun::star::awt::Point& aPoint ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL setSelection( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL copyText( sal_Int32 nStartIndex, sal_Int32 nEndIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleComponent
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL getAccessibleAtPoint( const ::com::sun::star::awt::Point& aPoint ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual void SAL_CALL grabFocus(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Int32 SAL_CALL getForeground(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Int32 SAL_CALL getBackground(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleExtendedComponent
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::XFont > SAL_CALL getFont(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual OUString SAL_CALL getTitledBorderText(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual OUString SAL_CALL getToolTipText(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleAction
    virtual sal_Int32 SAL_CALL getAccessibleActionCount( ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL doAccessibleAction ( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual OUString SAL_CALL getAccessibleActionDescription ( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleKeyBinding > SAL_CALL getAccessibleActionKeyBinding( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;

    // XAccessibleValue
    virtual ::com::sun::star::uno::Any SAL_CALL getCurrentValue(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual sal_Bool SAL_CALL setCurrentValue( const ::com::sun::star::uno::Any& aNumber ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Any SAL_CALL getMaximumValue(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
    virtual ::com::sun::star::uno::Any SAL_CALL getMinimumValue(  ) throw (::com::sun::star::uno::RuntimeException, std::exception) SAL_OVERRIDE;
};

#endif // INCLUDED_ACCESSIBILITY_INC_ACCESSIBILITY_STANDARD_VCLXACCESSIBLETOOLBOXITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
