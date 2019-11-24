/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:07:21 1999
 */
/* Compiler settings for D:\Projects\SDW V3\SourceContainer\SourceContainer.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SourceContainer_h__
#define __SourceContainer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWSourceContainer_FWD_DEFINED__
#define __ISDWSourceContainer_FWD_DEFINED__
typedef interface ISDWSourceContainer ISDWSourceContainer;
#endif 	/* __ISDWSourceContainer_FWD_DEFINED__ */


#ifndef __SDWSourceContainer_FWD_DEFINED__
#define __SDWSourceContainer_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWSourceContainer SDWSourceContainer;
#else
typedef struct SDWSourceContainer SDWSourceContainer;
#endif /* __cplusplus */

#endif 	/* __SDWSourceContainer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWSourceContainer_INTERFACE_DEFINED__
#define __ISDWSourceContainer_INTERFACE_DEFINED__

/* interface ISDWSourceContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWSourceContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B61E6A1-1503-11d3-A2B5-00801E00059A")
    ISDWSourceContainer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWEnable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWPush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWSourceContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWSourceContainer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWEnable )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisable )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWPush )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWSourceContainer __RPC_FAR * This);
        
        END_INTERFACE
    } ISDWSourceContainerVtbl;

    interface ISDWSourceContainer
    {
        CONST_VTBL struct ISDWSourceContainerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWSourceContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWSourceContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWSourceContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWSourceContainer_SDWEnable(This)	\
    (This)->lpVtbl -> SDWEnable(This)

#define ISDWSourceContainer_SDWDisable(This)	\
    (This)->lpVtbl -> SDWDisable(This)

#define ISDWSourceContainer_SDWPush(This)	\
    (This)->lpVtbl -> SDWPush(This)

#define ISDWSourceContainer_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWSourceContainer_SDWEnable_Proxy( 
    ISDWSourceContainer __RPC_FAR * This);


void __RPC_STUB ISDWSourceContainer_SDWEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSourceContainer_SDWDisable_Proxy( 
    ISDWSourceContainer __RPC_FAR * This);


void __RPC_STUB ISDWSourceContainer_SDWDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSourceContainer_SDWPush_Proxy( 
    ISDWSourceContainer __RPC_FAR * This);


void __RPC_STUB ISDWSourceContainer_SDWPush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSourceContainer_SDWInitialise_Proxy( 
    ISDWSourceContainer __RPC_FAR * This);


void __RPC_STUB ISDWSourceContainer_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWSourceContainer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
