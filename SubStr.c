/*
 * SubStr.c
 *
 *  Created on: 08-Nov-2015
 *      Author: joe
 */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

unsigned long tc, tots, co;

struct tmp {
	char val;
	char ch;
	struct tmp* a[27];
};

typedef struct tmp* node;

node uqchk;
char sr[15];
node st;
int valstrc = 0;

node init(void);

int uscrb(char*, node);
void recn(char*, int, int, node);
void substrgen(char*, node);
void sgen(char*, node, int, int, int, int);

int main() {

	st = init();

	printf("\nEnter a String of Characters");
	printf("\n\nThis program will print all possible, ");
	printf("\nGramatically valid Sub-Words\n\n");
	printf("Type \"Exit\" to end this program\n\n\n");


	char sr[20];
	while (1) {
		ip(sr);
		substrgen(sr, st);
	}

	return 0;
}

void substrgen(char *str, node st) {
	int n, i, j;
	n = strlen(str);
	clruq();
	valstrc = 0;
	for (i = 1; i <= n; i++) {
		fflush(stdout);
		sgen(str, st, 0, i, 0, n);
	}
	uscrb(str, st);
}

void sgen(char *str, node st, int spos, int mlen, int strsp, int sl) {
	static char tst[15];
	int i;
	if (spos == mlen - 1) {
		tst[spos] = '\0';
		uscrb(tst, st);

		return;
	}
	for (i = strsp; i < sl; i++) {
		tst[spos] = str[i];
		sgen(str, st, spos + 1, mlen, i + 1, sl);
	}
}

int uscrb(char *s, node st) {
	int n;
	n = strlen(s);
	recn(s, n, 0, st);
}

void recn(char *str, int n, int l, node st) {
	int i, j, f, k, xx = 0;
	static char tst[15], a[14];

	if (l == n) {
		for (i = 0; i < n; i++) {
			tst[i] = str[a[i]];
		}
		tst[i] = '\0';
		xx = chk(st, tst);
		if (xx) {
			valstrc++;
			if (!op(tst))
				printf("\n");
		}
		return;
	}
	for (i = 0; i < n; i++) {
		f = 0;
		for (j = 0; j < l; j++)
			if (a[j] == i)
				f = 1;

		if (!f) {
			a[l] = i;
			recn(str, n, l + 1, st);
		}
	}
}

node ma(void) {
	node x;
	int i;
	x = malloc(sizeof(struct tmp));
	if (x == NULL) {
		printf("\n\n\tallocation failed");
	}
	for (i = 0; i < 27; i++) {
		x->a[i] = NULL;
	}
	tots += sizeof(struct tmp);
	co++;
	x->ch = 'x';
	x->val = 0;
	return x;
}

int strins(node tx, char *a) {
	int k, charIns = 0, n;
	node tp;
	char t;

	k = 0;
	while (a[k]) {
		t = a[k];
		tc++;
		charIns++;
		if (t == '\'')
			n = 26;
		else
			n = t - 'a';
		if (t == '\0')
			tx->val = 1;
		else if (tx->a[n] == NULL) {
			tp = ma();
			tx->a[n] = tp;
			tx = tx->a[n];
		} else
			tx = tx->a[n];
		k++;
	}
	if (!tx->val)
		tx->val = 1;

	return charIns;
}

node init(void) {
	FILE *fp;
	int i, k, n, t;
	node tx, tp, st;
	char a[15];
	tc = 0;
	tots = 0;
	co = 0;
	fp = fopen("dict.txt", "r");

	if (fp == NULL) {
		char ttc[40];
		getcwd(ttc, 100);
		printf("\n\nThe Dictionary File(dict.txt) Could Not be Found in \n %s",
				ttc);
		exit(1);
	}
	fscanf(fp, "%s", a);
	i = 0;

	st = ma();
	if (st == NULL) {
		printf("\n\n Memory allocation failed");
		exit(0);
	}
	while (strcmp(a, "zzzzzz")) {
		i++;
//		printf("\n-->%s",a);
		strins(st, a);
		fscanf(fp, "%s", a);
	}

	printf("\nTotal characters : %ld", tc);
	printf("\nTotal nodes created : %ld", co);
	printf("\nTotal memory allocated = %ld\n\n", tots);
	tc = 0;

	return st;
}

int chk(node st, char* tst) {
	node tx = st;
	int i = 0, k;
	while (tst[i]) {
		if(tst[i]=='\'')
			k = 26;
		else
			k = tst[i] - 97;
		if (tx->a[k] == NULL)
			return 0;
		tx = tx->a[k];
		i++;
	}
	return tx->val;
}

void end() {

/*
 *
 *
 *
 *
 */

	exit(0);
}

void ip(char *s) {
	char tc;
	int i, l, f;

	printf("\n\nEnter a string('exit' to quit)  - ");

	scanf("%s", s);

	l = strlen(s);
	slwr(s);
	f = 0;
	for (i = 0; i < l; i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			continue;
		else if (s[i] == '\'')
			continue;
		else {
			f = 1;
			break;
		}
	}

	if (f) {
		printf("\nString Contains INVALID Characters...\n");
		printf("Enter Characters only from a-z and A_Z");
		s[0] = '\0';
		return;
	}

	if (!strcmp(s, "exit"))
		end();
	return;

}

void dealloc(node t) {
	int i;
	for (i = 0; i < 26; i++) {
		if (t->a[i])
			dealloc(t->a[i]);
	}
	free(t);
	return;
}

void clruq(void) {
	if (uqchk == NULL) {
		uqchk = ma();
		return;
	}
	dealloc(uqchk);
	uqchk = ma();
	return;

}

int op(char *str) {
	if (chk(uqchk, str))
		return 1;
	strins(uqchk, str);
	printf(" %s", str);
	return 0;
}

void slwr(char *s) {
	int i, l, d = 'a' - 'A';
	l = strlen(s);

	for (i = 0; i < l; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += d;
		}
	}

}
