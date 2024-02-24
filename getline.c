#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: parameter structure
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */

ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytesRead = 0;
    size_t lengthPointer = 0;
        if (!*length) /* if nothing left in the buffer, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        bytesRead = getline(buffer, &lengthPointer, stdin);
#else
        bytesRead = _getline(info, buffer, &lengthPointer);
#endif

	        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
                bytesRead--;
            }
            info->lineCountFlag = 1;
            removeComments(*buffer);
            buildHistoryList(info, *buffer, info->historyCount++);
            if (_strchr(*buffer, ';')) /* is this a command chain? */
            {
                *length = bytesRead;
                info->commandBuffer = buffer;
            }

	            }
    }
    return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter structure
 *
 * Return: bytes read
 */

ssize_t getInput(info_t *info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t x, y, length;
    ssize_t bytesRead = 0;
    char **bufferPointer = &(info->arg), *p;
    _putchar(BUF_FLUSH);
    bytesRead = bufferInput(info, &buffer, &length);
    if (bytesRead == -1) /* EOF */
        return (-1);

    if (length) /* we have commands left in the chain buffer */
    {
        y = x; /* init new iterator to current buffer position */
        p = buffer + x; /* get pointer for return */

	        checkChain(info, buffer, &y, x, length);

        while (y < length) /* iterate to semicolon or end */
        {
            if (isChain(info, buffer, &y))
                break;
            y++;
        }
        x = y + 1; /* increment past nulled ';'' */
        if (x >= length) /* reached end of buffer? */
        {
            x = length = 0; /* reset position and length */
            info->commandBufferType = CMD_NORM;
        }
        *bufferPointer = p; /* pass back pointer to current command position */
        return (_strlen(p)); /* return length of current command */
    }
    *bufferPointer = buffer; /* else not a chain, pass back buffer from _getline() */
    return (bytesRead); /* return length of buffer from _getline() */
}

/**
 * readBuffer - reads a buffer
 * @info: parameter structure
 * @buffer: buffer
 * @x: size
 *
 * Return: bytesRead
 */

ssize_t readBuffer(info_t *info, char *buffer, size_t *x)
{
    ssize_t bytesRead = 0;

    if (*x)
        return (0);
    bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);

    if (bytesRead >= 0)
        *x = bytesRead;
    return bytesRead;
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytesRead
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	    static char buffer[READ_BUF_SIZE];
    static size_t x, len;
    size_t k;
    ssize_t bytesRead = 0, bytesCopied = 0;
    char *p = NULL, *newP = NULL, *c;
    p = *ptr;

    if (p && length)
        bytesCopied = *length;

    if (x == len)
        x = len = 0;
    bytesRead = readBuffer(info, buffer, &len);

    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return (-1);
    c = _strchr(buffer + x, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : len;
    newP = _realloc(p, bytesCopied, bytesCopied ? bytesCopied + k : k + 1);

    if (!newP) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (bytesCopied)
        _strncat(newP, buffer + x, k - x);

    else
	            _strncpy(newP, buffer + x, k - x + );
    bytesCopied += k - x;
    x = k;
    p = newP;

    if (length)
        *length = bytesCopied;
    *ptr = p;
    return (bytesCopied);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sigNum)
{
    _puts("\n");
    _

puts("$ ");
    _putchar(BUF_FLUSH);
}
