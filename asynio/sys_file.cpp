#include "stdafx.h"
#include "sys_file.h"

#ifdef _MSC_VER
FILE_HANDLE by_file_open(const TCHAR *filepath, int flags, int mode)
{
	FILE_HANDLE fh;
	DWORD fileaccess = 0, fileshare = 0, filecreate = 0, fileattr = 0;

        /* decode the access flags */
	switch (flags & (O_RDONLY | O_WRONLY | O_RDWR)) {
	case O_RDONLY:         /* read access */
		fileaccess = GENERIC_READ;
		break;
	case O_WRONLY:         /* write access */
		fileaccess = GENERIC_WRITE;
		if ((flags & O_APPEND) != 0)
			fileaccess |= FILE_APPEND_DATA;
		break;
	case O_RDWR:           /* read and write access */
		fileaccess = GENERIC_READ | GENERIC_WRITE;
		if ((flags & O_APPEND) != 0)
			fileaccess = GENERIC_READ | FILE_APPEND_DATA;
		break;
	default:                /* error, bad flags */
		return FILE_INVALID;
	}

        /* decode open/create method flags */
	switch (flags & (O_CREAT | O_EXCL | O_TRUNC)) {
	case 0:
	case O_EXCL:            /* ignore EXCL w/o CREAT */
		filecreate = OPEN_EXISTING;
		break;
	case O_CREAT:
		filecreate = OPEN_ALWAYS;
		break;
	case O_CREAT | O_EXCL:
	case O_CREAT | O_TRUNC | O_EXCL:
		filecreate = CREATE_NEW;
		break;
	case O_TRUNC:
	case O_TRUNC | O_EXCL:  /* ignore EXCL w/o CREAT */
		filecreate = TRUNCATE_EXISTING;
		break;
	case O_CREAT | O_TRUNC:
		filecreate = CREATE_ALWAYS;
		break;
	default:
		return FILE_INVALID;
	}

	fileshare |= FILE_SHARE_READ | FILE_SHARE_WRITE;
	fileattr = FILE_ATTRIBUTE_NORMAL;

	fh = CreateFileW(filepath, fileaccess, fileshare, NULL,
			filecreate, fileattr, NULL);
	return fh;
}
int by_file_close(FILE_HANDLE fh)
{
	return CloseHandle(fh) ? 0 : -1;
}
_off_t by_lseek(FILE_HANDLE fh, _off_t offset, int whence)
{
	LARGE_INTEGER li;
	DWORD method;
	if (whence == SEEK_CUR)
		method = FILE_CURRENT;
	else if (whence == SEEK_SET)
		method = FILE_BEGIN;
	else if (whence == SEEK_END)
		method = FILE_END;
	else {
		return -1;
	}

	li.QuadPart = offset;
	li.LowPart = SetFilePointer(fh, li.LowPart, &li.HighPart, method);

	if (li.LowPart == 0xFFFFFFFF ) {
		li.QuadPart = -1;
	}
	return li.QuadPart;
}
int by_file_read(FILE_HANDLE fh, void *buf, size_t size)
{
	DWORD nRead = 0;
	if (!ReadFile(fh, buf, (DWORD) size, &nRead, NULL))
		return -1;
	return nRead;
}
int by_file_write(FILE_HANDLE fh, const void *buf, size_t size)
{
	DWORD nWritten = 0;
	if (!WriteFile(fh, buf, (DWORD) size, &nWritten, NULL))
		return -1;
	return nWritten;
}
byint64 by_file_fsize(FILE_HANDLE fh)
{
	DWORD  nLow, nHigh;
	byint64 n;
	nLow = GetFileSize(fh, &nHigh);
	if (nLow == 0xFFFFFFFF)
		return -1;
	n = nHigh;
	return nLow + (n << 32);
}
#else 
FILE_HANDLE by_file_open(const TCHAR *filepath, int flags, int mode)
{
	return open(filepath, flags, mode);
}
int by_file_close(FILE_HANDLE fh)
{
	return close(fh);
}
_off_t by_lseek(FILE_HANDLE fh, _off_t offset, int whence)
{
	return lseek(fh, offset, whence);
}
int by_file_read(FILE_HANDLE fh, void *buf, size_t size)
{
	return (int) read(fh, buf, size);
}
int by_file_write(FILE_HANDLE fh, const void *buf, size_t size)
{
	return (int) write(fh, buf, size);
}
byint64 by_file_fsize(FILE_HANDLE fh)
{
	struct stat  sbuf;
	if (fstat(fh, &sbuf) == -1)
		return -1;
	return sbuf.st_size;
}
#endif
