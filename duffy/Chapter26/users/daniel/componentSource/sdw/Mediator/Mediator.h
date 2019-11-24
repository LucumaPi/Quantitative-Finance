/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 10 10:36:07 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Mediator\Mediator.idl:
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

#ifndef __Mediator_h__
#define __Mediator_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWMediator_FWD_DEFINED__
#define __ISDWMediator_FWD_DEFINED__
typedef interface ISDWMediator ISDWMediator;
#endif 	/* __ISDWMediator_FWD_DEFINED__ */


#ifndef __SDWMediator_FWD_DEFINED__
#define __SDWMediator_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWMediator SDWMediator;
#else
typedef struct SDWMediator SDWMediator;
#endif /* __cplusplus */

#endif 	/* __SDWMediator_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWMediator_INTERFACE_DEFINED__
#define __ISDWMediator_INTERFACE_DEFINED__

/* interface ISDWMediator */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWMediator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DAC41FA1-0322-11d3-9BCB-0080AD712109")
    ISDWMediator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWEnable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWPush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWNotify( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWStartup( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWShutdown( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWMediatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWMediator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWMediator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWMediator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWEnable )( 
            ISDWMediator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisable )( 
            ISDWMediator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWPush )( 
            ISDWMediator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNotify )( 
            ISDWMediator __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWStartup )( 
            ISDWMediator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWShutdown )( 
            ISDWMediator __RPC_FAR * This);
        
        END_INTERFACE
    } ISDWMediatorVtbl;

    interface ISDWMediator
    {
        CONST_VTBL struct ISDWMediatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWMediator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWMediator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWMediator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWMediator_SDWEnable(This)	\
    (This)->lpVtbl -> SDWEnable(This)

#define ISDWMediator_SDWDisable(This)	\
    (This)->lpVtbl -> SDWDisable(This)

#define ISDWMediator_SDWPush(This)	\
    (This)->lpVtbl -> SDWPush(This)

#define ISDWMediator_SDWNotify(This,h,m)	\
    (This)->lpVtbl -> SDWNotify(This,h,m)

#define ISDWMediator_SDWStartup(This)	\
    (This)->lpVtbl -> SDWStartup(This)

#define ISDWMediator_SDWShutdown(This)	\
    (This)->lpVtbl -> SDWShutdown(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWMediator_SDWEnable_Proxy( 
    ISDWMediator __RPC_FAR * This);


void __RPC_STUB ISDWMediator_SDWEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWMediator_SDWDisable_Proxy( 
    ISDWMediator __RPC_FAR * This);


void __RPC_STUB ISDWMediator_SDWDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWMediator_SDWPush_Proxy( 
    ISDWMediator __RPC_FAR * This);


void __RPC_STUB ISDWMediator_SDWPush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWMediator_SDWNotify_Proxy( 
    ISDWMediator __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWMediator_SDWNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWMediator_SDWStartup_Proxy( 
    ISDWMediator __RPC_FAR * This);


void __RPC_STUB ISDWMediator_SDWStartup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWMediator_SDWShutdown_Proxy( 
    ISDWMediator __RPC_FAR * This);


void __RPC_STUB ISDWMediator_SDWShutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWMediator_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
