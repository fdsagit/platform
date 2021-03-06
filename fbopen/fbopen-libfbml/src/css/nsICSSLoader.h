/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1999
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#ifndef nsICSSLoader_h___
#define nsICSSLoader_h___

#include "nsISupports.h"
#include "nsSubstring.h"
#include "nsCompatibility.h"

class nsIAtom;
class nsIURI;
class nsICSSParser;
class nsICSSStyleSheet;
class nsPresContext;
class nsIContent;
class nsIParser;
class nsIDocument;
class nsIUnicharInputStream;
class nsICSSLoaderObserver;
class nsMediaList;
class nsICSSImportRule;

// IID for the nsICSSLoader interface
// 6c50f676-c764-4f2f-b62b-99d1076b44e9
#define NS_ICSS_LOADER_IID     \
{0x6c50f676, 0xc764, 0x4f2f, {0xb6, 0x2b, 0x99, 0xd1, 0x07, 0x6b, 0x44, 0xe9}}

typedef void (*nsCSSLoaderCallbackFunc)(nsICSSStyleSheet* aSheet, void *aData, PRBool aDidNotify);

class nsICSSLoader : public nsISupports {
public:
  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ICSS_LOADER_IID)

  NS_IMETHOD Init(nsIDocument* aDocument) = 0;
  NS_IMETHOD DropDocumentReference(void) = 0; // notification that doc is going away

  NS_IMETHOD SetCaseSensitive(PRBool aCaseSensitive) = 0;
  NS_IMETHOD SetCompatibilityMode(nsCompatibility aCompatMode) = 0;
  NS_IMETHOD SetPreferredSheet(const nsAString& aTitle) = 0;
  NS_IMETHOD GetPreferredSheet(nsAString& aTitle) = 0;

  // Get/Recycle a CSS parser for general use
  NS_IMETHOD GetParserFor(nsICSSStyleSheet* aSheet,
                          nsICSSParser** aParser) = 0;
  NS_IMETHOD RecycleParser(nsICSSParser* aParser) = 0;

  // XXX No one uses the aDefaultNameSpaceID params.... do we need them?
  
  // Load an inline style sheet
  // - if aCompleted is PR_TRUE, the sheet is fully loaded, don't
  //   block for it.
  // - if aCompleted is PR_FALSE, the sheet is still loading and 
  //   will be marked complete when complete
  NS_IMETHOD LoadInlineStyle(nsIContent* aElement,
                             nsIUnicharInputStream* aStream, 
                             PRUint32 aLineNumber,
                             const nsSubstring& aTitle, 
                             const nsSubstring& aMedia, 
                             nsIParser* aParserToUnblock,
                             PRBool& aCompleted,
                             nsICSSLoaderObserver* aObserver) = 0;

  // Load a linked style sheet
  // - if aCompleted is PR_TRUE, the sheet is fully loaded, don't
  //   block for it.
  // - if aCompleted is PR_FALSE, the sheet is still loading and 
  //   will be marked complete when complete
  NS_IMETHOD LoadStyleLink(nsIContent* aElement,
                           nsIURI* aURL, 
                           const nsSubstring& aTitle, 
                           const nsSubstring& aMedia, 
                           nsIParser* aParserToUnblock,
                           PRBool& aCompleted,
                           nsICSSLoaderObserver* aObserver) = 0;

  // Load a child style sheet (@import)
  NS_IMETHOD LoadChildSheet(nsICSSStyleSheet* aParentSheet,
                            nsIURI* aURL, 
                            nsMediaList* aMedia,
                            nsICSSImportRule* aRule) = 0;

  // Load a user agent or user sheet.  The sheet is loaded
  // synchronously, including @imports from it.
  NS_IMETHOD LoadAgentSheet(nsIURI* aURL, nsICSSStyleSheet** aSheet) = 0;

  // Load a user agent or user sheet.  The sheet is loaded
  // asynchronously and the observer notified when the load finishes.
  NS_IMETHOD LoadAgentSheet(nsIURI* aURL, nsICSSLoaderObserver* aObserver) = 0;

  // stop loading all sheets
  NS_IMETHOD Stop(void) = 0;

  // stop loading one sheet
  NS_IMETHOD StopLoadingSheet(nsIURI* aURL) = 0;

  /**
   * Whether the loader is enabled or not.
   * When disabled, processing of new styles is disabled and an attempt
   * to do so will fail with a return code of
   * NS_ERROR_NOT_AVAILABLE. Note that this DOES NOT disable
   * currently loading styles or already processed styles.
   */
  NS_IMETHOD GetEnabled(PRBool *aEnabled) = 0;
  NS_IMETHOD SetEnabled(PRBool aEnabled) = 0;
};

// IID for the nsICSSLoader_MOZILLA_1_8_BRANCH interface
// 8cee4512-b487-4573-8bcb-190d36fff66a
#define NS_ICSS_LOADER_MOZILLA_1_8_BRANCH_IID     \
{0x8cee4512, 0xb487, 0x4573, {0x8b, 0xcb, 0x19, 0x0d, 0x36, 0xff, 0xf6, 0x6a}}

class nsICSSLoader_MOZILLA_1_8_BRANCH : public nsISupports {
public:
  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ICSS_LOADER_MOZILLA_1_8_BRANCH_IID)

  // Load a sheet, with optional enabling of unsafe rules
  NS_IMETHOD LoadSheetSync(nsIURI* aURL, PRBool aEnableUnsafeRules, nsICSSStyleSheet** aSheet) = 0;
};

nsresult 
NS_NewCSSLoader(nsIDocument* aDocument, nsICSSLoader** aLoader);

nsresult 
NS_NewCSSLoader(nsICSSLoader** aLoader);

#endif /* nsICSSLoader_h___ */
