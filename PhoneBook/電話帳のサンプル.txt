#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//構造体宣言
typedef struct _card
{
	char name[10];		//名前
	char num[10];		//電話番号
	struct _card* next;	//次へのポインタ
}CARD;

//プロトタイプ宣言
void  add(char*, char*);
CARD* search(char*, int);

CARD* start = NULL;//先頭を覚えておくポインタ

int main(void)
{
	int i;
	char cmd[10], name[10], num[10];

	printf("*******    電話帳アプリ    *******\n");
	printf("追　加　→ add    名前 電話番号\n");
	printf("検　索　→ search 名前\n");
	printf("全件表示→ list\n");
	printf("\n");

	while (1)	//ずっと繰り返し(exitコマンドでbreak)
	{
		//コマンドの入力
		scanf_s("%s", cmd, 10);
		//大文字で入力した場合でも小文字に変換する
		for (i = 0; i < strlen(cmd); i++)
			cmd[i] 
			= 
			tolower(cmd[i]);

		if (strcmp(cmd, "exit") == 0)
		{
			//exitコマンドの場合
			break;
		}
		else if (strcmp(cmd, "add") == 0)
		{
			//addコマンドの場合
			//名前、電話番号を入力
			scanf_s("%s", name, 10);
			scanf_s("%s", num, 10);
			//追加処理
			add(name, num);
		}
		else if (strcmp(cmd, "list") == 0)
		{
			//listコマンドの場合
			//全件画面表示
			CARD* card = start;
			while (card != NULL)
			{
				printf("%s %s\n", card->name, card->num);
				card = card->next;
			}
		}
		else if (strcmp(cmd, "search") == 0)
		{
			//searchコマンドの場合
			//名前を入力
			scanf_s("%s", name, 10);
			//検索結果を画面表示
			CARD* card = search(name,0);
			if (card != NULL)
			{
				printf("%s %s\n", card->name, card->num);
			}
			else
			{
				printf("%s の登録がありません。\n",name);
			}
		}
	}
}

void add(char* name, char* num)
{
	//新しい領域を確保
	CARD* newCard = (CARD*)malloc(sizeof(CARD)),*beforeCard;
	//名前と電話番号を新しい領域に設定
	strcpy(newCard->name, name);
	strcpy(newCard->num, num);

	//挿入位置を検索し、前のカードのnextと自分自身のnextを設定
	beforeCard = search(name, 1);
	if (beforeCard == NULL)
	{
		if (start == NULL)
		{
			//１つも登録がない場合
			newCard->next = NULL;
		}
		else
		{
			//追加したカードが先頭の場合
			newCard->next = start;
		}
		start = newCard;
	}
	else
	{
		newCard->next = beforeCard->next;
		beforeCard->next = newCard;
	}
}

CARD* search(char* name,int flg) //flg:0=名前が一致したアドレスを返す 1:ひとつ前のアドレスを返す
{
	CARD* p = start,*bf=NULL;
	if (start == NULL)
	{
		//１つも登録がない場合NULLを返す
		return NULL;
	}
	else
	{
		if (flg == 0)
		{
			//名前が一致するものを探す
			while (p != NULL && strcmp(name,p->name) != 0)
			{
				p = p->next;
			}
			return p;
		}
		else
		{
			//a-z順で追加する位置を探す
			while (p != NULL && strcmp(name, p->name) >= 0)
			{
				bf = p;
				p = p->next;
			}
			return bf;
		}
	}

}
