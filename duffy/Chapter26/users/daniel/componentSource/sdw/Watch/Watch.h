/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:02:04 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Watch\Watch.idl:
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

#ifndef __Watch_h__
#define __Watch_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWWatch_FWD_DEFINED__
#define __ISDWWatch_FWD_DEFINED__
typedef interface ISDWWatch ISDWWatch;
#endif 	/* __ISDWWatch_FWD_DEFINED__ */


#ifndef __SDWWatch_FWD_DEFINED__
#define __SDWWatch_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWWatch SDWWatch;
#else
typedef struct SDWWatch SDWWatch;
#endif /* __cplusplus */

#endif 	/* __SDWWatch_FWD_DEFINED__ */


/* header files for imported files */
#include "sdwconnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWWatch_INTERFACE_DEFINED__
#define __ISDWWatch_INTERFACE_DEFINED__

/* interface ISDWWatch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWWatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2FF25391-03AA-11d3-A29E-00801E00059A")
    ISDWWatch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWIncrement_h( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWIncrement_m( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWTime( 
            /* [in] */ long hours,
            /* [in] */ long minutes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWUnfreeze( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWFreeze( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWDisplay( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWHours( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWMinutes( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWWatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWWatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWWatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWIncrement_h )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWIncrement_m )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWTime )( 
            ISDWWatch __RPC_FAR * This,
            /* [in] */ long hours,
            /* [in] */ long minutes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWUnfreeze )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWFreeze )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisplay )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWHours )( 
            ISDWWatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWMinutes )( 
            ISDWWatch __RPC_FAR * This);
        
        END_INTERFACE
    } ISDWWatchVtbl;

    interface ISDWWatch
    {
        CONST_VTBL struct ISDWWatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWWatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWWatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWWatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWWatch_SDWIncrement_h(This)	\
    (This)->lpVtbl -> SDWIncrement_h(This)

#define ISDWWatch_SDWIncrement_m(This)	\
    (This)->lpVtbl -> SDWIncrement_m(This)

#define ISDWWatch_SDWTime(This,hours,minutes)	\
    (This)->lpVtbl -> SDWTime(This,hours,minutes)

#define ISDWWatch_SDWUnfreeze(This)	\
    (This)->lpVtbl -> SDWUnfreeze(This)

#define ISDWWatch_SDWFreeze(This)	\
    (This)->lpVtbl -> SDWFreeze(This)

#define ISDWWatch_SDWDisplay(This)	\
    (This)->lpVtbl -> SDWDisplay(This)

#define ISDWWatch_SDWHours(This)	\
    (This)->lpVtbl -> SDWHours(This)

#define ISDWWatch_SDWMinutes(This)	\
    (This)->lpVtbl -> SDWMinutes(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWWatch_SDWIncrement_h_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWIncrement_h_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWIncrement_m_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWIncrement_m_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWTime_Proxy( 
    ISDWWatch __RPC_FAR * This,
    /* [in] */ long hours,
    /* [in] */ long minutes);


void __RPC_STUB ISDWWatch_SDWTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWUnfreeze_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWUnfreeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWFreeze_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWFreeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWDisplay_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWHours_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWHours_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWWatch_SDWMinutes_Proxy( 
    ISDWWatch __RPC_FAR * This);


void __RPC_STUB ISDWWatch_SDWMinutes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWWatch_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
