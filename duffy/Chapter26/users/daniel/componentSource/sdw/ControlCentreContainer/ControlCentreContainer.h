/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:57:53 1999
 */
/* Compiler settings for D:\Projects\SDW V3\ControlCentreContainer\ControlCentreContainer.idl:
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

#ifndef __ControlCentreContainer_h__
#define __ControlCentreContainer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWControlCentreContainer_FWD_DEFINED__
#define __ISDWControlCentreContainer_FWD_DEFINED__
typedef interface ISDWControlCentreContainer ISDWControlCentreContainer;
#endif 	/* __ISDWControlCentreContainer_FWD_DEFINED__ */


#ifndef __SDWControlCentreContainer_FWD_DEFINED__
#define __SDWControlCentreContainer_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWControlCentreContainer SDWControlCentreContainer;
#else
typedef struct SDWControlCentreContainer SDWControlCentreContainer;
#endif /* __cplusplus */

#endif 	/* __SDWControlCentreContainer_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWControlCentreContainer_INTERFACE_DEFINED__
#define __ISDWControlCentreContainer_INTERFACE_DEFINED__

/* interface ISDWControlCentreContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWControlCentreContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8888231-16C3-11d3-A912-0080AD712109")
    ISDWControlCentreContainer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWEnable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWPush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWNotify( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWControlCentreContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWControlCentreContainer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWControlCentreContainer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWControlCentreContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWEnable )( 
            ISDWControlCentreContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisable )( 
            ISDWControlCentreContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWPush )( 
            ISDWControlCentreContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNotify )( 
            ISDWControlCentreContainer __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWControlCentreContainer __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        END_INTERFACE
    } ISDWControlCentreContainerVtbl;

    interface ISDWControlCentreContainer
    {
        CONST_VTBL struct ISDWControlCentreContainerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWControlCentreContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWControlCentreContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWControlCentreContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWControlCentreContainer_SDWEnable(This)	\
    (This)->lpVtbl -> SDWEnable(This)

#define ISDWControlCentreContainer_SDWDisable(This)	\
    (This)->lpVtbl -> SDWDisable(This)

#define ISDWControlCentreContainer_SDWPush(This)	\
    (This)->lpVtbl -> SDWPush(This)

#define ISDWControlCentreContainer_SDWNotify(This,h,m)	\
    (This)->lpVtbl -> SDWNotify(This,h,m)

#define ISDWControlCentreContainer_SDWInitialise(This,h,m)	\
    (This)->lpVtbl -> SDWInitialise(This,h,m)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWControlCentreContainer_SDWEnable_Proxy( 
    ISDWControlCentreContainer __RPC_FAR * This);


void __RPC_STUB ISDWControlCentreContainer_SDWEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentreContainer_SDWDisable_Proxy( 
    ISDWControlCentreContainer __RPC_FAR * This);


void __RPC_STUB ISDWControlCentreContainer_SDWDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentreContainer_SDWPush_Proxy( 
    ISDWControlCentreContainer __RPC_FAR * This);


void __RPC_STUB ISDWControlCentreContainer_SDWPush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentreContainer_SDWNotify_Proxy( 
    ISDWControlCentreContainer __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWControlCentreContainer_SDWNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentreContainer_SDWInitialise_Proxy( 
    ISDWControlCentreContainer __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWControlCentreContainer_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWControlCentreContainer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
