#pragma once

#ifdef __cplusplus
extern "C" {
	namespace NT {
#endif

		typedef struct _UNICODE_STRING {
			USHORT Length;
			USHORT MaximumLength;
#ifdef MIDL_PASS
			[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT * Buffer;
#else // MIDL_PASS
			_Field_size_bytes_part_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
		} UNICODE_STRING;
		typedef UNICODE_STRING *PUNICODE_STRING;
		typedef const UNICODE_STRING *PCUNICODE_STRING;

		typedef long NTSTATUS;

		typedef struct QueryDirectoryObjectBuffer_t {
			UNICODE_STRING DirectoryEntry;
			UNICODE_STRING DirectoryEntryType;
			char Buffer[1000];
		} QUERYDIRECTORYOBJECTBUFFER, *PQUERYDIRECTORYOBJECTBUFFER;

		typedef struct _OBJECT_ATTRIBUTES {
			ULONG Length;
			HANDLE RootDirectory;
			PUNICODE_STRING ObjectName;
			ULONG Attributes;
			PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
			PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
		} OBJECT_ATTRIBUTES;
		typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;
		typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

		typedef ULONG ACCESS_MASK;
		typedef ACCESS_MASK *PACCESS_MASK;

#define InitializeObjectAttributes( p, n, a, r, s ) { \
	(p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
	(p)->RootDirectory = r;                             \
	(p)->Attributes = a;                                \
	(p)->ObjectName = n;                                \
	(p)->SecurityDescriptor = s;                        \
	(p)->SecurityQualityOfService = NULL;               \
				}

#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)

#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

#define EVENT_QUERY_STATE       0x0001
#define EVENT_MODIFY_STATE      0x0002  
#define EVENT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3) 

		typedef struct _OBJECT_DIRECTORY_INFORMATION {
			UNICODE_STRING Name;
			UNICODE_STRING TypeName;
		} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

		typedef enum _OBJECT_INFORMATION_CLASS {
			ObjectBasicInformation,
			ObjectNameInformation,
			ObjectTypeInformation,
			ObjectAllInformation,
			ObjectDataInformation
		} OBJECT_INFORMATION_CLASS;

		typedef enum _THREAD_INFORMATION_CLASS {
			ThreadBasicInformation, ThreadTimes, ThreadPriority, ThreadBasePriority, ThreadAffinityMask,
			ThreadImpersonationToken, ThreadDescriptorTableEntry, ThreadEnableAlignmentFaultFixup, ThreadEventPair,
			ThreadQuerySetWin32StartAddress, ThreadZeroTlsCell, ThreadPerformanceCount, ThreadAmILastThread,
			ThreadIdealProcessor, ThreadPriorityBoost, ThreadSetTlsArrayAddress, ThreadIsIoPending, ThreadHideFromDebugger
		} THREAD_INFORMATION_CLASS, *PTHREAD_INFORMATION_CLASS;
		typedef enum _POOL_TYPE {
			NonPagedPool,
			NonPagedPoolExecute = NonPagedPool,
			PagedPool,
			NonPagedPoolMustSucceed = NonPagedPool + 2,
			DontUseThisType,
			NonPagedPoolCacheAligned = NonPagedPool + 4,
			PagedPoolCacheAligned,
			NonPagedPoolCacheAlignedMustS = NonPagedPool + 6,
			MaxPoolType,
			NonPagedPoolBase = 0,
			NonPagedPoolBaseMustSucceed = NonPagedPoolBase + 2,
			NonPagedPoolBaseCacheAligned = NonPagedPoolBase + 4,
			NonPagedPoolBaseCacheAlignedMustS = NonPagedPoolBase + 6,
			NonPagedPoolSession = 32,
			PagedPoolSession = NonPagedPoolSession + 1,
			NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
			DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
			NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
			PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
			NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,
			NonPagedPoolNx = 512,
			NonPagedPoolNxCacheAligned = NonPagedPoolNx + 4,
			NonPagedPoolSessionNx = NonPagedPoolNx + 32
		} POOL_TYPE;

		typedef enum _PROCESS_INFORMATION_CLASS {
			ProcessBasicInformation, ProcessQuotaLimits, ProcessIoCounters, ProcessVmCounters, ProcessTimes,
			ProcessBasePriority, ProcessRaisePriority, ProcessDebugPort, ProcessExceptionPort, ProcessAccessToken,
			ProcessLdtInformation, ProcessLdtSize, ProcessDefaultHardErrorMode, ProcessIoPortHandlers,
			ProcessPooledUsageAndLimits, ProcessWorkingSetWatch, ProcessUserModeIOPL, ProcessEnableAlignmentFaultFixup,
			ProcessPriorityClass, ProcessWx86Information, ProcessHandleCount, ProcessAffinityMask, ProcessPriorityBoost, MaxProcessInfoClass
		} PROCESS_INFORMATION_CLASS, *PPROCESS_INFORMATION_CLASS;

		typedef struct _OBJECT_BASIC_INFORMATION {
			ULONG Attributes;
			ACCESS_MASK DesiredAccess;
			ULONG HandleCount;
			ULONG ReferenceCount;
			ULONG PagedPoolUsage;
			ULONG NonPagedPoolUsage;
			ULONG Reserved[3];
			ULONG NameInformationLength;
			ULONG TypeInformationLength;
			ULONG SecurityDescriptorLength;
			LARGE_INTEGER CreationTime;
		} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

		typedef struct _SEMAPHORE_BASIC_INFORMATION {
			ULONG CurrentCount;
			ULONG MaximumCount;
		} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;

		typedef struct _OBJECT_NAME_INFORMATION {
			UNICODE_STRING Name;
			WCHAR NameBuffer[1];
		} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

		typedef enum _EVENT_INFORMATION_CLASS {
			EventBasicInformation
		} EVENT_INFORMATION_CLASS, *PEVENT_INFORMATION_CLASS;

		typedef enum _EVENT_TYPE {
			NotificationEvent,
			SynchronizationEvent
		} EVENT_TYPE, *PEVENT_TYPE;

		typedef struct _EVENT_BASIC_INFORMATION {
			EVENT_TYPE              EventType;
			LONG                    EventState;
		} EVENT_BASIC_INFORMATION, *PEVENT_BASIC_INFORMATION;

		typedef enum _SEMAPHORE_INFO_CLASS {
			SemaphoreBasicInfo
		} SEMAPHORE_INFO_CLASS;

		typedef enum _MUTANT_INFORMATION_CLASS {
			MutantBasicInformation
		} MUTANT_INFORMATION_CLASS;

		typedef struct _MUTANT_BASIC_INFORMATION {
			LONG CurrentCount;
			BOOLEAN OwnedByCaller;
			BOOLEAN AbandonedState;
		} MUTANT_BASIC_INFORMATION, *PMUTANT_BASIC_INFORMATION;

		NTSTATUS
			NTAPI
			NtQueryMutant(
			IN HANDLE MutantHandle,
			IN MUTANT_INFORMATION_CLASS MutantInformationClass,
			OUT PVOID MutantInformation,
			IN ULONG MutantInformationLength,
			OUT PULONG ResultLength OPTIONAL);

		NTSTATUS
			NTAPI
			NtQuerySemaphore(
			IN HANDLE hSemaphore,
			IN SEMAPHORE_INFO_CLASS SemaphoreInfoClass,
			OUT PVOID Buffer,
			IN ULONG BufferSize,
			OUT PULONG BytesReturned
			);

		typedef struct _OBJECT_TYPE_INFORMATION {
			UNICODE_STRING TypeName;
			ULONG TotalNumberOfHandles;
			ULONG TotalNumberOfObjects;
			WCHAR Unused1[8];
			ULONG HighWaterNumberOfHandles;
			ULONG HighWaterNumberOfObjects;
			WCHAR Unused2[8];
			ACCESS_MASK InvalidAttributes;
			GENERIC_MAPPING GenericMapping;
			ACCESS_MASK ValidAttributes;
			BOOLEAN SecurityRequired;
			BOOLEAN MaintainHandleCount;
			USHORT MaintainTypeList;
			POOL_TYPE PoolType;
			ULONG DefaultPagedPoolCharge;
			ULONG DefaultNonPagedPoolCharge;
		} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

		typedef struct _OBJECT_DATA_INFORMATION {
			BOOLEAN InheritHandle;
			BOOLEAN ProtectFromClose;
		} OBJECT_DATA_INFORMATION, *POBJECT_DATA_INFORMATION;

		typedef struct _OBJECT_ALL_INFORMATION {
			ULONG NumberOfObjectsTypes;
			OBJECT_TYPE_INFORMATION ObjectTypeInformation[1];
		} OBJECT_ALL_INFORMATION, *POBJECT_ALL_INFORMATION;

		typedef enum _SECTION_INFORMATION_CLASS {
			SectionBasicInformation,
			SectionImageInformation
		} SECTION_INFORMATION_CLASS, *PSECTION_INFORMATION_CLASS;

		typedef struct _SECTION_BASIC_INFORMATION {
			ULONG Unknown;
			ULONG SectionAttributes;
			LARGE_INTEGER SectionSize;
		} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

		typedef struct _SECTION_IMAGE_INFORMATION {
			PVOID EntryPoint;
			ULONG StackZeroBits;
			ULONG StackReserved;
			ULONG StackCommit;
			ULONG ImageSubsystem;
			WORD SubSystemVersionLow;
			WORD SubSystemVersionHigh;
			ULONG Unknown1;
			ULONG ImageCharacteristics;
			ULONG ImageMachineType;
			ULONG Unknown2[3];
		} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

		typedef struct _CLIENT_ID {
			HANDLE UniqueProcess;
			HANDLE UniqueThread;
		} CLIENT_ID;
		typedef CLIENT_ID *PCLIENT_ID;

		typedef struct _IO_STATUS_BLOCK {
			union {
				NTSTATUS Status;
				PVOID Pointer;
			} DUMMYUNIONNAME;
			ULONG_PTR Information;
		} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

		typedef struct _RTL_DRIVE_LETTER_CURDIR {
			USHORT Flags;
			USHORT Length;
			ULONG TimeStamp;
			UNICODE_STRING DosPath;
		} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

		typedef struct _RTL_USER_PROCESS_PARAMETERS {
			ULONG MaximumLength;
			ULONG Length;
			ULONG Flags;
			ULONG DebugFlags;
			PVOID ConsoleHandle;
			ULONG ConsoleFlags;
			HANDLE StdInputHandle;
			HANDLE StdOutputHandle;
			HANDLE StdErrorHandle;
			UNICODE_STRING CurrentDirectoryPath;
			HANDLE CurrentDirectoryHandle;
			UNICODE_STRING DllPath;
			UNICODE_STRING ImagePathName;
			UNICODE_STRING CommandLine;
			PVOID Environment;
			ULONG StartingPositionLeft;
			ULONG StartingPositionTop;
			ULONG Width;
			ULONG Height;
			ULONG CharWidth;
			ULONG CharHeight;
			ULONG ConsoleTextAttributes;
			ULONG WindowFlags;
			ULONG ShowWindowFlags;
			UNICODE_STRING WindowTitle;
			UNICODE_STRING DesktopName;
			UNICODE_STRING ShellInfo;
			UNICODE_STRING RuntimeData;
			RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
		} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

		typedef struct _PEB_LDR_DATA {
			ULONG Length;
			BOOLEAN Initialized;
			PVOID SsHandle;
			LIST_ENTRY InLoadOrderModuleList;
			LIST_ENTRY InMemoryOrderModuleList;
			LIST_ENTRY InInitializationOrderModuleList;
		} PEB_LDR_DATA, *PPEB_LDR_DATA;

		typedef void(*PPEBLOCKROUTINE)(
			PVOID PebLock);

		typedef struct _PEB_FREE_BLOCK {
			_PEB_FREE_BLOCK *Next;
			ULONG Size;
		} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

		typedef struct _PEB {
			BOOLEAN InheritedAddressSpace;
			BOOLEAN ReadImageFileExecOptions;
			BOOLEAN BeingDebugged;
			BOOLEAN Spare;
			HANDLE Mutant;
			PVOID ImageBaseAddress;
			PPEB_LDR_DATA LoaderData;
			PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
			PVOID SubSystemData;
			PVOID ProcessHeap;
			PVOID FastPebLock;
			PPEBLOCKROUTINE FastPebLockRoutine;
			PPEBLOCKROUTINE FastPebUnlockRoutine;
			ULONG EnvironmentUpdateCount;
			PVOID* KernelCallbackTable;
			PVOID EventLogSection;
			PVOID EventLog;
			PPEB_FREE_BLOCK FreeList;
			ULONG TlsExpansionCounter;
			PVOID TlsBitmap;
			ULONG TlsBitmapBits[0x2];
			PVOID ReadOnlySharedMemoryBase;
			PVOID ReadOnlySharedMemoryHeap;
			PVOID* ReadOnlyStaticServerData;
			PVOID AnsiCodePageData;
			PVOID OemCodePageData;
			PVOID UnicodeCaseTableData;
			ULONG NumberOfProcessors;
			ULONG NtGlobalFlag;
			BYTE Spare2[0x4];
			LARGE_INTEGER CriticalSectionTimeout;
			ULONG HeapSegmentReserve;
			ULONG HeapSegmentCommit;
			ULONG HeapDeCommitTotalFreeThreshold;
			ULONG HeapDeCommitFreeBlockThreshold;
			ULONG NumberOfHeaps;
			ULONG MaximumNumberOfHeaps;
			PVOID **ProcessHeaps;
			PVOID GdiSharedHandleTable;
			PVOID ProcessStarterHelper;
			PVOID GdiDCAttributeList;
			PVOID LoaderLock;
			ULONG OSMajorVersion;
			ULONG OSMinorVersion;
			ULONG OSBuildNumber;
			ULONG OSPlatformId;
			ULONG ImageSubSystem;
			ULONG ImageSubSystemMajorVersion;
			ULONG ImageSubSystemMinorVersion;
			ULONG GdiHandleBuffer[0x22];
			ULONG PostProcessInitRoutine;
			ULONG TlsExpansionBitmap;
			BYTE TlsExpansionBitmapBits[0x80];
			ULONG SessionId;
		} PEB, *PPEB;

		typedef struct _TEB {
			NT_TIB Tib;
			PVOID EnvironmentPointer;
			CLIENT_ID Cid;
			PVOID ActiveRpcInfo;
			PVOID ThreadLocalStoragePointer;
			PPEB Peb;
			ULONG LastErrorValue;
			ULONG CountOfOwnedCriticalSections;
			PVOID CsrClientThread;
			PVOID Win32ThreadInfo;
			ULONG Win32ClientInfo[0x1F];
			PVOID WOW32Reserved;
			ULONG CurrentLocale;
			ULONG FpSoftwareStatusRegister;
			PVOID SystemReserved1[0x36];
			PVOID Spare1;
			ULONG ExceptionCode;
			ULONG SpareBytes1[0x28];
			PVOID SystemReserved2[0xA];
			ULONG GdiRgn;
			ULONG GdiPen;
			ULONG GdiBrush;
			CLIENT_ID RealClientId;
			PVOID GdiCachedProcessHandle;
			ULONG GdiClientPID;
			ULONG GdiClientTID;
			PVOID GdiThreadLocaleInfo;
			PVOID UserReserved[5];
			PVOID GlDispatchTable[0x118];
			ULONG GlReserved1[0x1A];
			PVOID GlReserved2;
			PVOID GlSectionInfo;
			PVOID GlSection;
			PVOID GlTable;
			PVOID GlCurrentRC;
			PVOID GlContext;
			NTSTATUS LastStatusValue;
			UNICODE_STRING StaticUnicodeString;
			WCHAR StaticUnicodeBuffer[0x105];
			PVOID DeallocationStack;
			PVOID TlsSlots[0x40];
			LIST_ENTRY TlsLinks;
			PVOID Vdm;
			PVOID ReservedForNtRpc;
			PVOID DbgSsReserved[0x2];
			ULONG HardErrorDisabled;
			PVOID Instrumentation[0x10];
			PVOID WinSockData; 
			ULONG GdiBatchCount; 
			ULONG Spare2; ULONG Spare3; ULONG Spare4; 
			PVOID ReservedForOle; 
			ULONG WaitingOnLoaderLock; 
			PVOID StackCommit; 
			PVOID StackCommitMax; 
			PVOID StackReserved;

		} TEB, *PTEB;
		typedef enum _FILE_INFORMATION_CLASS {
			FileDirectoryInformation = 1, FileFullDirectoryInformation, FileBothDirectoryInformation, FileBasicInformation,
			FileStandardInformation, FileInternalInformation, FileEaInformation, FileAccessInformation, FileNameInformation,
			FileRenameInformation, FileLinkInformation, FileNamesInformation, FileDispositionInformation, FilePositionInformation,
			FileFullEaInformation, FileModeInformation, FileAlignmentInformation, FileAllInformation, FileAllocationInformation,
			FileEndOfFileInformation, FileAlternateNameInformation, FileStreamInformation, FilePipeInformation, FilePipeLocalInformation,
			FilePipeRemoteInformation, FileMailslotQueryInformation, FileMailslotSetInformation, FileCompressionInformation,
			FileCopyOnWriteInformation, FileCompletionInformation, FileMoveClusterInformation, FileQuotaInformation,
			FileReparsePointInformation, FileNetworkOpenInformation, FileObjectIdInformation, FileTrackingInformation,
			FileOleDirectoryInformation, FileContentIndexInformation, FileInheritContentIndexInformation, FileOleInformation, FileMaximumInformation
		} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;


#define NtCurrentProcess() ( (HANDLE)(LONG_PTR) -1 )  
#define ZwCurrentProcess() NtCurrentProcess()         
#define NtCurrentThread() ( (HANDLE)(LONG_PTR) -2 )   
#define ZwCurrentThread() NtCurrentThread()           
#define NtCurrentSession() ( (HANDLE)(LONG_PTR) -3 )  
#define ZwCurrentSession() NtCurrentSession()         

		NTSTATUS
			NTAPI
			NtSetInformationThread(
			IN HANDLE ThreadHandle,
			IN THREAD_INFORMATION_CLASS ThreadInformationClass,
			IN PVOID ThreadInformation,
			IN ULONG ThreadInformationLength);

		NTSTATUS
			NTAPI
			NtQuerySection(
			IN HANDLE SectionHandle,
			IN SECTION_INFORMATION_CLASS InformationClass,
			OUT PVOID InformationBuffer,
			IN ULONG InformationBufferSize,
			OUT PULONG ResultLength OPTIONAL);

		NTSTATUS
			NTAPI
			NtOpenDirectoryObject(
			OUT PHANDLE hDirectory,
			IN ACCESS_MASK AccessMask,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtQueryInformationFile(
			IN HANDLE FileHandle, OUT PIO_STATUS_BLOCK IoStatusBlock, OUT PVOID FileInformation, IN ULONG Length, IN FILE_INFORMATION_CLASS FileInformationClass);

		NTSTATUS
			NTAPI
			NtQueryInformationThread(
			IN HANDLE ThreadHandle,
			IN THREAD_INFORMATION_CLASS ThreadInformationClass,
			OUT PVOID ThreadInformation,
			IN ULONG ThreadInformationLength,
			OUT PULONG ReturnLength OPTIONAL);

		NTSTATUS
			NTAPI
			NtQueryInformationProcess(
			IN HANDLE ProcessHandle,
			IN PROCESS_INFORMATION_CLASS ProcessInformationClass,
			OUT PVOID ProcessInformation,
			IN ULONG ProcessInformationLength,
			OUT PULONG ReturnLength);

		NTSTATUS
			NTAPI
			NtQueryDirectoryObject(
			IN HANDLE hDirectory,
			OUT POBJECT_DIRECTORY_INFORMATION DirectoryEntryBuffer,
			IN ULONG DirectoryEntryBufferSize,
			IN BOOLEAN  bOnlyFirstEntry,
			IN BOOLEAN bFirstEntry,
			IN PULONG  EntryIndex,
			OUT PULONG  BytesReturned
			);

		NTSTATUS
			NTAPI
			NtOpenMutant(
			OUT PHANDLE hMutex,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenSemaphore(
			OUT PHANDLE hSemaphore,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenSection(
			OUT PHANDLE phSection,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenIoCompletion(
			OUT PHANDLE phIoCompletionPort,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenFile(
			OUT PHANDLE phFile,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			OUT PIO_STATUS_BLOCK pIoStatusBlock,
			IN ULONG ShareMode,
			IN ULONG OpenMode
			);

		NTSTATUS
			NTAPI
			NtSetInformationProcess(
			IN HANDLE ProcessHandle,
			IN PROCESS_INFORMATION_CLASS ProcessInformationClass,
			IN PVOID ProcessInformation,
			IN ULONG ProcessInformationLength);
		NTSTATUS
			NTAPI
			NtOpenJobObject(
			OUT PHANDLE phJob,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenProcess(
			OUT PHANDLE phProcess,
			IN ACCESS_MASK AccessMask,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			IN PCLIENT_ID pClientId
			);

		NTSTATUS
			NTAPI
			NtOpenEventPair(
			OUT PHANDLE hEventPair,
			IN ACCESS_MASK AccessMask,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenTimer(
			OUT PHANDLE phTimer,
			IN ACCESS_MASK AccessMask,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenKey(
			OUT PHANDLE phKey,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes
			);

		NTSTATUS
			NTAPI
			NtOpenThread(
			OUT PHANDLE phThread,
			IN ACCESS_MASK AccessMask,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			IN PCLIENT_ID pClientId
			);

		NTSTATUS
			NTAPI
			NtOpenProcessToken(
			IN HANDLE hProcess,
			IN ACCESS_MASK DesiredAccess,
			OUT PHANDLE phToken
			);

		NTSTATUS
			NTAPI
			NtOpenThreadToken(
			IN HANDLE hThread,
			IN ACCESS_MASK DesiredAccess,
			IN BOOLEAN bUseContextOfProcess,
			OUT PHANDLE phToken
			);

		NTSTATUS NTAPI NtLoadDriver(IN PUNICODE_STRING DriverServiceName);

		VOID
			NTAPI
			RtlInitUnicodeString(
			_Out_ PUNICODE_STRING DestinationString,
			_In_opt_z_ __drv_aliasesMem PCWSTR SourceString
			);

		NTSTATUS NTAPI NtOpenSymbolicLinkObject(
			_Out_  PHANDLE LinkHandle,
			_In_   ACCESS_MASK DesiredAccess,
			_In_   POBJECT_ATTRIBUTES ObjectAttributes
			);


		NTSTATUS NTAPI NtQuerySymbolicLinkObject(
			_In_       HANDLE LinkHandle,
			_Inout_    PUNICODE_STRING LinkTarget,
			_Out_opt_  PULONG ReturnedLength
			);

		NTSTATUS NTAPI NtOpenEvent(
			_Out_  PHANDLE EventHandle,
			_In_   ACCESS_MASK DesiredAccess,
			_In_   POBJECT_ATTRIBUTES ObjectAttributes
			);


		NTSTATUS NTAPI NtQueryEvent(
			IN HANDLE               EventHandle,
			IN EVENT_INFORMATION_CLASS EventInformationClass,
			OUT PVOID               EventInformation,
			IN ULONG                EventInformationLength,
			OUT PULONG              ReturnLength OPTIONAL);



		NTSTATUS
			NTAPI
			NtQuerySecurityObject(
			IN HANDLE hObject,
			IN SECURITY_INFORMATION SecurityInfoRequested,
			IN PSECURITY_DESCRIPTOR pSecurityDescriptor,
			IN ULONG pSecurityDescriptorLength,
			OUT PULONG BytesRequired
			);

		NTSTATUS
			NTAPI
			NtQueryObject(
			IN HANDLE hObject,
			IN OBJECT_INFORMATION_CLASS ObjectInfoClass,
			OUT PVOID Buffer,
			IN ULONG BufferSize,
			OUT PULONG BytesReturned
			);

		NTSTATUS NTAPI
			NtQuerySecurityObject(
			IN HANDLE hObject,
			IN SECURITY_INFORMATION SecurityInfoRequested,
			IN PSECURITY_DESCRIPTOR pSecurityDescriptor,
			IN ULONG pSecurityDescriptorLength,
			OUT PULONG BytesRequired
			);

#ifdef __cplusplus
	}
}
#endif

