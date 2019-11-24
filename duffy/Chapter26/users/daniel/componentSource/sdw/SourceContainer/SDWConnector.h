/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:07:22 1999
 */
/* Compiler settings for D:\Projects\SDW V3\SDWConnector.idl:
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

#ifndef __SDWConnector_h__
#define __SDWConnector_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWConnector_FWD_DEFINED__
#define __ISDWConnector_FWD_DEFINED__
typedef interface ISDWConnector ISDWConnector;
#endif 	/* __ISDWConnector_FWD_DEFINED__ */


#ifndef __SDWConnector_FWD_DEFINED__
#define __SDWConnector_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWConnector SDWConnector;
#else
typedef struct SDWConnector SDWConnector;
#endif /* __cplusplus */

#endif 	/* __SDWConnector_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWConnector_INTERFACE_DEFINED__
#define __ISDWConnector_INTERFACE_DEFINED__

/* interface ISDWConnector */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWConnector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4317D81-02E2-11d3-A29C-00801E00059A")
    ISDWConnector : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWSetLowerConnection( 
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWSetUpperConnection( 
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWKillConnection( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWConnectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWConnector __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWConnector __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWConnector __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWSetLowerConnection )( 
            ISDWConnector __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWSetUpperConnection )( 
            ISDWConnector __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWKillConnection )( 
            ISDWConnector __RPC_FAR * This);
        
        END_INTERFACE
    } ISDWConnectorVtbl;

    interface ISDWConnector
    {
        CONST_VTBL struct ISDWConnectorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWConnector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWConnector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWConnector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWConnector_SDWSetLowerConnection(This,pUnk)	\
    (This)->lpVtbl -> SDWSetLowerConnection(This,pUnk)

#define ISDWConnector_SDWSetUpperConnection(This,pUnk)	\
    (This)->lpVtbl -> SDWSetUpperConnection(This,pUnk)

#define ISDWConnector_SDWKillConnection(This)	\
    (This)->lpVtbl -> SDWKillConnection(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWConnector_SDWSetLowerConnection_Proxy( 
    ISDWConnector __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB ISDWConnector_SDWSetLowerConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConnector_SDWSetUpperConnection_Proxy( 
    ISDWConnector __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB ISDWConnector_SDWSetUpperConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConnector_SDWKillConnection_Proxy( 
    ISDWConnector __RPC_FAR * This);


void __RPC_STUB ISDWConnector_SDWKillConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWConnector_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
