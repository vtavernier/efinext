#include <efi.h>
#include <efilib.h>

#define TARGET_BOOTID 0

const EFI_GUID EFI_VENDOR = { 0x8BE4DF61, 0x93CA, 0x11D2, { 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C } };

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);

	Print(L"Setting BootNext value to 0x%04x\n", (UINT32)(TARGET_BOOTID));

	// Set BootNext
	UINT16 Target = TARGET_BOOTID;
	EFI_STATUS Status = uefi_call_wrapper(RT->SetVariable, 5, L"BootNext", &EFI_VENDOR, EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, sizeof(Target), &Target);
	if (Status != EFI_SUCCESS) {
		Print(L"Failed to set BootNext value: %d\n", (UINT32)Target);
		// Wait for 10s
		uefi_call_wrapper(BS->Stall, 1, 10000000);
	}

	Print(L"Resetting system now.\n");
	uefi_call_wrapper(RT->ResetSystem, 4, EfiResetCold, EFI_SUCCESS, 0, NULL);

	return EFI_SUCCESS;
}
