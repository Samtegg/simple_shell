#include "shell.h"

/**
 * dinput_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t dinput_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t dr = 0;
	size_t dlen_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, dsigintHandler);
#if USE_GETLINE
		dr = dgetline(buf, &len_p, stdin);
#else
		dr = _dgetline(info, buf, &dlen_p);
#endif
		if (dr > 0)
		{
			if ((*buf)[dr - 1] == '\n')
			{
				(*buf)[dr - 1] = '\0'; /* remove trailing newline */
				dr--;
			}
			info->linecount_flag = 1;
			dremove_comments(*buf);
			dbuild_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = dr;
				info->cmd_buf = buf;
			}
		}
	}
	return (dr);
}

/**
 * dget_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t dget_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t di, dj, dlen;
	ssize_t dr = 0;
	char **dbuf_p = &(info->arg), *dp;

	_dputchar(BUF_FLUSH);
	dr = dinput_buf(info, &buf, &dlen);
	if (dr == -1) /* EOF */
		return (-1);
	if (dlen)	/* we have commands left in the chain buffer */
	{
		dj = di; /* init new iterator to current buf position */
		dp = buf + di; /* get pointer for return */

		dcheck_chain(info, buf, &dj, di, dlen);
		while (dj < dlen) /* iterate to semicolon or end */
		{
			if (dis_chain(info, buf, &dj))
				break;
			dj++;
		}

		di = dj + 1; /* increment past nulled ';'' */
		if (di >= dlen) /* reached end of buffer? */
		{
			di = dlen = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*dbuf_p = dp; /* pass back pointer to current command position */
		return (_dstrlen(dp)); /* return length of current command */
	}

	*dbuf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (dr); /* return length of buffer from _getline() */
}

/**
 * dread_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t dr = 0;

	if (*i)
		return (0);
	dr = read(info->readfd, buf, READ_BUF_SIZE);
	if (dr >= 0)
		*i = dr;
	return (dr);
}

/**
 * _dgetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _dgetline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t di, dlen;
	size_t dk;
	ssize_t dr = 0, ds = 0;
	char *dp = NULL, *dnew_p = NULL, *dc;

	dp = *ptr;
	if (dp && length)
		ds = *length;
	if (di == dlen)
		di = dlen = 0;

	dr = read_buf(info, buf, &dlen);
	if (dr == -1 || (dr == 0 && dlen == 0))
		return (-1);

	dc = _dstrchr(buf + di, '\n');
	dk = dc ? 1 + (unsigned int)(dc - buf) : dlen;
	dnew_p = _drealloc(dp, ds, ds ? ds + dk : dk + 1);
	if (!dnew_p) /* MALLOC FAILURE! */
		return (dp ? free(dp), -1 : -1);

	if (ds)
		_dstrncat(dnew_p, buf + di, dk - di);
	else
		_dstrncpy(dnew_p, buf + di, dk - di + 1);

	ds += dk - di;
	di = dk;
	dp = dnew_p;

	if (length)
		*length = ds;
	*ptr = dp;
	return (ds);
}

/**
 * dsigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void dsigintHandler(__attribute__((unused))int sig_num)
{
	_dputs("\n");
	_dputs("$ ");
	_dputchar(BUF_FLUSH);
}
