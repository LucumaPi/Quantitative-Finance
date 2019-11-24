/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:58:17 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Converter\converter.idl:
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

#ifndef __converter_h__
#define __converter_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWConverter_FWD_DEFINED__
#define __ISDWConverter_FWD_DEFINED__
typedef interface ISDWConverter ISDWConverter;
#endif 	/* __ISDWConverter_FWD_DEFINED__ */


#ifndef __SDWConverter_FWD_DEFINED__
#define __SDWConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWConverter SDWConverter;
#else
typedef struct SDWConverter SDWConverter;
#endif /* __cplusplus */

#endif 	/* __SDWConverter_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWConverter_INTERFACE_DEFINED__
#define __ISDWConverter_INTERFACE_DEFINED__

/* interface ISDWConverter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EF552731-FE2E-11d2-A291-00801E00059A")
    ISDWConverter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWEnable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWUpdate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWValue( 
            /* [out] */ long __RPC_FAR *value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWConverter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWConverter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWEnable )( 
            ISDWConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisable )( 
            ISDWConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWUpdate )( 
            ISDWConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWValue )( 
            ISDWConverter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *value);
        
        END_INTERFACE
    } ISDWConverterVtbl;

    interface ISDWConverter
    {
        CONST_VTBL struct ISDWConverterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWConverter_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#define ISDWConverter_SDWEnable(This)	\
    (This)->lpVtbl -> SDWEnable(This)

#define ISDWConverter_SDWDisable(This)	\
    (This)->lpVtbl -> SDWDisable(This)

#define ISDWConverter_SDWUpdate(This)	\
    (This)->lpVtbl -> SDWUpdate(This)

#define ISDWConverter_SDWValue(This,value)	\
    (This)->lpVtbl -> SDWValue(This,value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWConverter_SDWInitialise_Proxy( 
    ISDWConverter __RPC_FAR * This);


void __RPC_STUB ISDWConverter_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConverter_SDWEnable_Proxy( 
    ISDWConverter __RPC_FAR * This);


void __RPC_STUB ISDWConverter_SDWEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConverter_SDWDisable_Proxy( 
    ISDWConverter __RPC_FAR * This);


void __RPC_STUB ISDWConverter_SDWDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConverter_SDWUpdate_Proxy( 
    ISDWConverter __RPC_FAR * This);


void __RPC_STUB ISDWConverter_SDWUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWConverter_SDWValue_Proxy( 
    ISDWConverter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *value);


void __RPC_STUB ISDWConverter_SDWValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWConverter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
