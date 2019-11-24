/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:57:41 1999
 */
/* Compiler settings for D:\Projects\SDW V3\ControlCentre\ControlCentre.idl:
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

#ifndef __ControlCentre_h__
#define __ControlCentre_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWControlCentre_FWD_DEFINED__
#define __ISDWControlCentre_FWD_DEFINED__
typedef interface ISDWControlCentre ISDWControlCentre;
#endif 	/* __ISDWControlCentre_FWD_DEFINED__ */


#ifndef __SDWControlCentre_FWD_DEFINED__
#define __SDWControlCentre_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWControlCentre SDWControlCentre;
#else
typedef struct SDWControlCentre SDWControlCentre;
#endif /* __cplusplus */

#endif 	/* __SDWControlCentre_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWControlCentre_INTERFACE_DEFINED__
#define __ISDWControlCentre_INTERFACE_DEFINED__

/* interface ISDWControlCentre */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWControlCentre;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4556D321-0386-11d3-A29E-00801E00059A")
    ISDWControlCentre : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWAccept( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWNoaccept( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWPush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWUpdate( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWState( 
            /* [out] */ long __RPC_FAR *state) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWControlCentreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWControlCentre __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWControlCentre __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWControlCentre __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWControlCentre __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWAccept )( 
            ISDWControlCentre __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNoaccept )( 
            ISDWControlCentre __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWPush )( 
            ISDWControlCentre __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWUpdate )( 
            ISDWControlCentre __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWState )( 
            ISDWControlCentre __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *state);
        
        END_INTERFACE
    } ISDWControlCentreVtbl;

    interface ISDWControlCentre
    {
        CONST_VTBL struct ISDWControlCentreVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWControlCentre_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWControlCentre_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWControlCentre_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWControlCentre_SDWInitialise(This,h,m)	\
    (This)->lpVtbl -> SDWInitialise(This,h,m)

#define ISDWControlCentre_SDWAccept(This)	\
    (This)->lpVtbl -> SDWAccept(This)

#define ISDWControlCentre_SDWNoaccept(This)	\
    (This)->lpVtbl -> SDWNoaccept(This)

#define ISDWControlCentre_SDWPush(This)	\
    (This)->lpVtbl -> SDWPush(This)

#define ISDWControlCentre_SDWUpdate(This,h,m)	\
    (This)->lpVtbl -> SDWUpdate(This,h,m)

#define ISDWControlCentre_SDWState(This,state)	\
    (This)->lpVtbl -> SDWState(This,state)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWInitialise_Proxy( 
    ISDWControlCentre __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWControlCentre_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWAccept_Proxy( 
    ISDWControlCentre __RPC_FAR * This);


void __RPC_STUB ISDWControlCentre_SDWAccept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWNoaccept_Proxy( 
    ISDWControlCentre __RPC_FAR * This);


void __RPC_STUB ISDWControlCentre_SDWNoaccept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWPush_Proxy( 
    ISDWControlCentre __RPC_FAR * This);


void __RPC_STUB ISDWControlCentre_SDWPush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWUpdate_Proxy( 
    ISDWControlCentre __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWControlCentre_SDWUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWControlCentre_SDWState_Proxy( 
    ISDWControlCentre __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *state);


void __RPC_STUB ISDWControlCentre_SDWState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWControlCentre_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
