# efinext

efinext is a small EFI program that changes the value of the BootNext variable to the boot option chosen
(statically) in [main.c](main.c) by the `TARGET_BOOTID` definition.

Is compiled using `make`, provided the [gnu-efi](https://sourceforge.net/projects/gnu-efi/) development
package is installed.

## Usage

Install the produced binary in your EFI system partition, and create a boot entry for it using efibootmgr:

	# Depends on your distro
	export EFIDIR=/boot/efi

	mkdir $EFIDIR/EFI/efinext/
	cp build/efinext.efi $EFIDIR/EFI/efinext/
	efibootmgr --create --disk /dev/sdX --part Y --loader /EFI/efinext/efinext.efi --label "Boot entry 0"

Note that you may have to adapt those commands if you choose to use the MOK-signed version, and thus boot
this program using the shim loader.

## License

The code in this repository is public domain.

## Author

Vincent Tavernier <vince.tavernier@gmail.com>
