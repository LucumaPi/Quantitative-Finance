/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:00:28 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Router\Router.idl:
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

#ifndef __Router_h__
#define __Router_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWRouter_FWD_DEFINED__
#define __ISDWRouter_FWD_DEFINED__
typedef interface ISDWRouter ISDWRouter;
#endif 	/* __ISDWRouter_FWD_DEFINED__ */


#ifndef __SDWRouter_FWD_DEFINED__
#define __SDWRouter_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWRouter SDWRouter;
#else
typedef struct SDWRouter SDWRouter;
#endif /* __cplusplus */

#endif 	/* __SDWRouter_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWRouter_INTERFACE_DEFINED__
#define __ISDWRouter_INTERFACE_DEFINED__

/* interface ISDWRouter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWRouter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("330EE391-03B9-11d3-A29E-00801E00059A")
    ISDWRouter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWNotify( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWRouterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWRouter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWRouter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWRouter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWRouter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNotify )( 
            ISDWRouter __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        END_INTERFACE
    } ISDWRouterVtbl;

    interface ISDWRouter
    {
        CONST_VTBL struct ISDWRouterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWRouter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWRouter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWRouter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWRouter_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#define ISDWRouter_SDWNotify(This,h,m)	\
    (This)->lpVtbl -> SDWNotify(This,h,m)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWRouter_SDWInitialise_Proxy( 
    ISDWRouter __RPC_FAR * This);


void __RPC_STUB ISDWRouter_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWRouter_SDWNotify_Proxy( 
    ISDWRouter __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWRouter_SDWNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWRouter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
