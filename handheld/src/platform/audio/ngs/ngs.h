#ifndef NGS_H
#define NGS_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <psp2/types.h>

#define SCE_NGS_MAKE_PARAMS_ID(module_id, index, ver)  ( ((module_id) & 0x0000ffff) | (((ver) & 0x000000ff) << 16) | (((index) & 0x000000ff) << 24) )

#define SCE_NGS_FAILED(r)       ((r) != SCE_NGS_OK)
#define SCE_NGS_SUCCESS(r)      ((r) == SCE_NGS_OK)

#define SCE_NGS_INVALID_HANDLE      (0)
#define SCE_NGS_MEMORY_ALIGN_SIZE   (16)

#define SCE_NGS_MAX_SYSTEM_CHANNELS (2)

#define SCE_NGS_VOICE_PATCH_AUTO_SUBINDEX   (-1)

typedef SceUInt32 SceNgsModuleID;
typedef SceUInt32 SceNgsParamsID;
typedef SceUInt32 SceNgsHVoice;
typedef SceUInt32 SceNgsHPatch;
typedef SceUInt32 SceNgsHSynSystem;
typedef SceUInt32 SceNgsHRack;

typedef struct SceNgsModuleParamHeader {
    SceInt32    moduleId;
    SceInt32    chan;
} SceNgsModuleParamHeader;

typedef struct SceNgsParamsDescriptor {
    SceNgsParamsID  id;
    SceUInt32       size;
} SceNgsParamsDescriptor;

struct SceNgsVoiceDefinition;

typedef struct SceNgsBufferInfo {
    void        *data;
    SceUInt32   size;
} SceNgsBufferInfo;

typedef struct SceNgsVoicePreset {
    SceInt32    nNameOffset;
    SceUInt32   uNameLength;
    SceInt32    nPresetDataOffset;
    SceUInt32   uSizePresetData;
    SceInt32    nBypassFlagsOffset;
    SceUInt32   uNumBypassFlags;
} SceNgsVoicePreset;


typedef struct SceNgsSystemInitParams {
    SceInt32 nMaxRacks;
    SceInt32 nMaxVoices;
    SceInt32 nGranularity;
    SceInt32 nSampleRate;
    SceInt32 nMaxModules;
} SceNgsSystemInitParams;

typedef struct SceNgsRackDescription {
    const struct SceNgsVoiceDefinition* pVoiceDefn;
    SceInt32    nVoices;
    SceInt32    nChannelsPerVoice;
    SceInt32    nMaxPatchesPerInput;
    SceInt32    nPatchesPerOutput;
    void*       pUserReleaseData;
} SceNgsRackDescription;

typedef struct SceNgsPatchSetupInfo {
    SceNgsHVoice    hVoiceSource;
    SceInt32        nSourceOutputIndex;
    SceInt32        nSourceOutputSubIndex;
    SceNgsHVoice    hVoiceDestination;
    SceInt32        nTargetInputIndex;
} SceNgsPatchSetupInfo;

typedef struct SceNgsVolumeMatrix {
    SceFloat32 m[SCE_NGS_MAX_SYSTEM_CHANNELS][SCE_NGS_MAX_SYSTEM_CHANNELS];
} SceNgsVolumeMatrix;

typedef struct SceNgsPatchRouteInfo {
    SceInt32 nOutputChannels;
    SceInt32 nInputChannels;
    SceNgsVolumeMatrix vols;
} SceNgsPatchRouteInfo;

typedef struct SceNgsVoiceInfo {
    SceUInt32 uVoiceState;
    SceUInt32 uNumModules;
    SceUInt32 uNumInputs;
    SceUInt32 uNumOutputs;
    SceUInt32 uNumPatchesPerOutput;
    SceUInt32 uUpdateCallsActive;
} SceNgsVoiceInfo;

typedef struct SceNgsCallbackInfo {
    SceNgsHVoice    hVoiceHandle;
    SceNgsHRack     hRackHandle;
    SceNgsModuleID  uModuleID;
    SceInt32        nCallbackData;
    SceInt32        nCallbackData2;
    void*           pCallbackPtr;
    void*           pUserData;
} SceNgsCallbackInfo;

typedef void (*SceNgsCallbackFunc) (const SceNgsCallbackInfo* pCallbackInfo);

typedef SceNgsCallbackFunc SceNgsRackReleaseCallbackFunc;
typedef SceNgsCallbackFunc SceNgsModuleCallbackFunc;
typedef SceNgsCallbackFunc SceNgsParamsErrorCallbackFunc;

SceInt32 sceNgsSystemGetRequiredMemorySize( const SceNgsSystemInitParams* pSynthParams, SceUInt32* pnSize );
SceInt32 sceNgsSystemInit( void* pSynthSysMemory, const SceUInt32 uMemSize, const SceNgsSystemInitParams* pSynthParams, SceNgsHSynSystem* pSystemHandle );
SceInt32 sceNgsSystemUpdate( SceNgsHSynSystem hSystemHandle );
SceInt32 sceNgsSystemRelease( SceNgsHSynSystem hSystemHandle );
SceInt32 sceNgsSystemLock( SceNgsHSynSystem hSystemHandle );
SceInt32 sceNgsSystemUnlock( SceNgsHSynSystem hSystemHandle );
SceInt32 sceNgsSystemSetParamErrorCallback( SceNgsHSynSystem hSystemHandle, const SceNgsParamsErrorCallbackFunc callbackFuncPtr );
SceInt32 sceNgsSystemSetFlags( SceNgsHSynSystem hSystemHandle, const SceUInt32 uSystemFlags );


SceInt32 sceNgsRackGetRequiredMemorySize( SceNgsHSynSystem hSystemHandle, const SceNgsRackDescription* pRackDesc, SceUInt32* pnSize );
SceInt32 sceNgsRackInit( SceNgsHSynSystem hSystemHandle, SceNgsBufferInfo* pRackBuffer, const SceNgsRackDescription* pRackDesc, SceNgsHRack* pRackHandle );
SceInt32 sceNgsRackGetVoiceHandle( SceNgsHRack hRackHandle, const SceUInt32 uIndex, SceNgsHVoice* pVoiceHandle );
SceInt32 sceNgsRackRelease( SceNgsHRack hRackHandle,  const SceNgsRackReleaseCallbackFunc callbackFuncPtr );
SceInt32 sceNgsRackSetParamErrorCallback(SceNgsHRack hRackHandle, const SceNgsParamsErrorCallbackFunc callbackFuncPtr );

SceInt32 sceNgsVoiceInit( SceNgsHVoice hVoiceHandle, const SceNgsVoicePreset* pPreset, const SceUInt32 uInitFlags );

SceInt32 sceNgsVoicePlay( SceNgsHVoice hVoiceHandle );
SceInt32 sceNgsVoiceKeyOff( SceNgsHVoice hVoiceHandle );
SceInt32 sceNgsVoiceKill( SceNgsHVoice hVoiceHandle );
SceInt32 sceNgsVoicePause( SceNgsHVoice hVoiceHandle );
SceInt32 sceNgsVoiceResume( SceNgsHVoice hVoiceHandle );

SceInt32 sceNgsVoiceSetPreset( SceNgsHVoice hVoiceHandle, const SceNgsVoicePreset* pVoicePreset );
SceInt32 sceNgsVoiceLockParams( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceNgsParamsID uParamsInterfaceId, SceNgsBufferInfo* pParamsBuffer);
SceInt32 sceNgsVoiceUnlockParams( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule );
SceInt32 sceNgsVoiceSetParamsBlock( SceNgsHVoice hVoiceHandle, const SceNgsModuleParamHeader* pParamData, const SceUInt32 uSize, SceInt32* pnErrorCount );

SceInt32 sceNgsVoiceBypassModule( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceUInt32 uBypassFlag );
SceInt32 sceNgsVoiceSetModuleCallback( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, const SceNgsModuleCallbackFunc callbackFuncPtr, void* pUserData );
SceInt32 sceNgsVoiceSetFinishedCallback( SceNgsHVoice hVoiceHandle, const SceNgsCallbackFunc callbackFuncPtr, void* pUserData );
SceInt32 sceNgsVoiceGetStateData( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, void* pMem, const SceUInt32 uMemSize );
SceInt32 sceNgsVoiceGetInfo( SceNgsHVoice hVoiceHandle, SceNgsVoiceInfo* pInfo );
SceInt32 sceNgsVoiceGetModuleType( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, SceNgsModuleID* pModuleType );
SceInt32 sceNgsVoiceGetModuleBypass( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, SceUInt32* puBypassFlag );
SceInt32 sceNgsVoiceGetParamsOutOfRange( SceNgsHVoice hVoiceHandle, const SceUInt32 uModule, char* pszMessageBuffer );

SceInt32 sceNgsPatchCreateRouting( const SceNgsPatchSetupInfo* pPatchInfo, SceNgsHPatch* pPatchHandle );
SceInt32 sceNgsPatchGetInfo( SceNgsHPatch hPatchHandle, SceNgsPatchRouteInfo* pRouteInfo, SceNgsPatchSetupInfo* pSetup );
SceInt32 sceNgsVoiceGetOutputPatch( SceNgsHVoice hVoiceHandle, const SceInt32 nOutputIndex, const SceInt32 nSubIndex, SceNgsHPatch* pPatchHandle );
SceInt32 sceNgsPatchRemoveRouting( SceNgsHPatch hPatchHandle );
SceInt32 sceNgsVoicePatchSetVolume( SceNgsHPatch hPatchHandle, const SceInt32 nOutputChannel, const SceInt32 nInputChannel, const SceFloat32 fVol );
SceInt32 sceNgsVoicePatchSetVolumes( SceNgsHPatch hPatchHandle, const SceInt32 nOutputChannel, const SceFloat32* pVolumes, const SceInt32 nVols );
SceInt32 sceNgsVoicePatchSetVolumesMatrix( SceNgsHPatch hPatchHandle, const SceNgsVolumeMatrix* pMatrix );

SceInt32 sceNgsModuleGetNumPresets( SceNgsHSynSystem hSystemHandle, const SceNgsModuleID uModuleID, SceUInt32* puNumPresets );
SceInt32 sceNgsModuleGetPreset( SceNgsHSynSystem hSystemHandle, const SceNgsModuleID uModuleID, const SceUInt32 uPresetIndex, SceNgsBufferInfo* pParamsBuffer );






/* Module ID */
#define SCE_NGS_PLAYER_ID                   (0x5CE6)

/* User Params ID */
#define SCE_NGS_PLAYER_PARAMS_STRUCT_ID     (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PLAYER_ID,1,1))

#define SCE_NGS_PLAYER_MAX_BUFFERS (4)

#define SCE_NGS_PLAYER_LOOP_CONTINUOUS (-1)
#define SCE_NGS_PLAYER_NO_NEXT_BUFFER (-1)
#define SCE_NGS_PLAYER_MAX_PCM_CHANNELS (2)
#define SCE_NGS_PLAYER_MAX_OCTAVE_CHANGE (2)

#define SCE_NGS_PLAYER_STREAMING (0)
#define SCE_NGS_PLAYER_RESIDENT (1)

#define SCE_NGS_PLAYER_LEFT_CHANNEL (0)
#define SCE_NGS_PLAYER_RIGHT_CHANNEL (1)
#define SCE_NGS_PLAYER_NULL_CHANNEL (-1)

#define SCE_NGS_PLAYER_TYPE_PCM (0)
#define SCE_NGS_PLAYER_TYPE_ADPCM (1)

#define SCE_NGS_PLAYER_END_OF_DATA (0)
#define SCE_NGS_PLAYER_SWAPPED_BUFFER (1)
#define SCE_NGS_PLAYER_LOOPED_BUFFER (2)

typedef struct SceNgsPlayerBufferParams {
	const void* pBuffer;
	SceInt32 nNumBytes;
	SceInt16 nLoopCount;
	SceInt16 nNextBuff;
} SceNgsPlayerBufferParams;

typedef struct SceNgsPlayerStates {
	SceInt32 nCurrentBytePositionInBuffer;
	SceInt32 nCurrentBuffer;
	SceInt32 nSamplesGeneratedSinceKeyOn;
	SceInt32 nBytesConsumedSinceKeyOn;
	SceInt32 nSamplesGeneratedTotal;
	SceInt32 nBytesConsumedTotal;
} SceNgsPlayerStates;

typedef struct SceNgsPlayerParams {
	SceNgsParamsDescriptor    desc;
	SceNgsPlayerBufferParams  buffs[SCE_NGS_PLAYER_MAX_BUFFERS];
	SceFloat32                fPlaybackFrequency;
	SceFloat32                fPlaybackScalar;
	SceInt32                  nLeadInSamples;
	SceInt32                  nLimitNumberOfSamplesPlayed;
	SceInt32                  nStartByte;
	SceInt8                   nChannels;
	SceInt8                   nChannelMap[SCE_NGS_PLAYER_MAX_PCM_CHANNELS];
	SceInt8                   nType;
	SceInt8                   reserved;
	SceInt8                   nStartBuffer;
	SceInt8                   pad[2];
} SceNgsPlayerParams;





#define SCE_NGS_SIMPLE_VOICE_PCM_PLAYER      (0)
#define SCE_NGS_SIMPLE_VOICE_EQ              (1)
#define SCE_NGS_SIMPLE_VOICE_ENVELOPE        (2)
#define SCE_NGS_SIMPLE_VOICE_PAUSER          (3)
#define SCE_NGS_SIMPLE_VOICE_SEND_1_FILTER   (4)
#define SCE_NGS_SIMPLE_VOICE_SEND_2_FILTER   (5)

#define SCE_NGS_SIMPLE_VOICE_NUM_MODULES     (6)

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleVoice(void);




#define SCE_NGS_MASTER_BUSS_OUTPUT_MODULE   (1)

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetMasterBuss(void);


#if defined(__cplusplus)
}
#endif

#endif /* NGS_H */