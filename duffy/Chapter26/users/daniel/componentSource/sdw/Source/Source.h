/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:01:12 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Source\Source.idl:
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

#ifndef __Source_h__
#define __Source_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWSource_FWD_DEFINED__
#define __ISDWSource_FWD_DEFINED__
typedef interface ISDWSource ISDWSource;
#endif 	/* __ISDWSource_FWD_DEFINED__ */


#ifndef __SDWSource_FWD_DEFINED__
#define __SDWSource_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWSource SDWSource;
#else
typedef struct SDWSource SDWSource;
#endif /* __cplusplus */

#endif 	/* __SDWSource_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWSource_INTERFACE_DEFINED__
#define __ISDWSource_INTERFACE_DEFINED__

/* interface ISDWSource */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E76B41D1-FBE6-11D2-89C1-00104B428F17")
    ISDWSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWEnable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWUpdate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWState( 
            /* [out] */ long __RPC_FAR *value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWEnable )( 
            ISDWSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisable )( 
            ISDWSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWUpdate )( 
            ISDWSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWState )( 
            ISDWSource __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *value);
        
        END_INTERFACE
    } ISDWSourceVtbl;

    interface ISDWSource
    {
        CONST_VTBL struct ISDWSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWSource_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#define ISDWSource_SDWEnable(This)	\
    (This)->lpVtbl -> SDWEnable(This)

#define ISDWSource_SDWDisable(This)	\
    (This)->lpVtbl -> SDWDisable(This)

#define ISDWSource_SDWUpdate(This)	\
    (This)->lpVtbl -> SDWUpdate(This)

#define ISDWSource_SDWState(This,value)	\
    (This)->lpVtbl -> SDWState(This,value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWSource_SDWInitialise_Proxy( 
    ISDWSource __RPC_FAR * This);


void __RPC_STUB ISDWSource_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSource_SDWEnable_Proxy( 
    ISDWSource __RPC_FAR * This);


void __RPC_STUB ISDWSource_SDWEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSource_SDWDisable_Proxy( 
    ISDWSource __RPC_FAR * This);


void __RPC_STUB ISDWSource_SDWDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSource_SDWUpdate_Proxy( 
    ISDWSource __RPC_FAR * This);


void __RPC_STUB ISDWSource_SDWUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWSource_SDWState_Proxy( 
    ISDWSource __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *value);


void __RPC_STUB ISDWSource_SDWState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWSource_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
