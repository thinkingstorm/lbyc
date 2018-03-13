#ifndef SYS_FILE_H_
#define SYS_FILE_H_


#ifdef _MSC_VER

#define FILE_HANDLE		HANDLE
#define FILE_INVALID	INVALID_HANDLE_VALUE

#elif defined(__GNUC__)

# define	FILE_HANDLE		int
# define	FILE_INVALID	(int) -1
#endif

FILE_HANDLE by_file_open(const TCHAR *filepath, int flags, int mode);
int by_file_close(FILE_HANDLE fh);
_off_t by_lseek(FILE_HANDLE fh, _off_t offset, int whence);
int by_file_read(FILE_HANDLE fh, void *buf, size_t size);
int by_file_write(FILE_HANDLE fh, const void *buf, size_t size);
byint64 by_file_fsize(FILE_HANDLE fh);



#endif // !SYS_FILE_H_
