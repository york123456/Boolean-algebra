#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//aa+a'b'+(a+c)af
void translate(char str[],char var[] ,int &nstr, int &nvar)
{
	int k, i, j;

	for (i = 0; i < nstr; i++)
	{
		if (str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122)
		{
			k = 1;
			for (j = 0; j < nvar; j++)
			{
				if (str[i] == var[j])
				{
					k = 0;
				}
			}
			if (k == 1)
			{
				var[nvar] = str[i];
				nvar++;
			}
		}
	}

	for (i = 0; i < nvar; i++)
		printf("%d %c\n", i, var[i]);
	printf("\n");





	// 消空格
	for (i = 0; i < nstr; i++)
	{
		if (str[i] == ' ')
		{
			for (j = i; j < nstr; j++)
			{
				str[j] = str[j + 1];
			}
			nstr--;
		}
	}



	//加括號
	for (i = nstr; i > 0; i--)
	{
		str[i] = str[i - 1];
	}
	str[0] = '(';
	str[nstr + 1] = ')';
	nstr = nstr + 2;




	//標準化
	for (i = 0; i < nstr; i++)
	{
		if ((str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122) && (str[i + 1] >= 65 && str[i + 1] <= 90 || str[i + 1] >= 97 && str[i + 1] <= 122))  //aa-->a.a
		{
			for (j = nstr; j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i + 1] = '.';
			nstr++;
		}
		if ((str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122) && str[i + 1] == '(')  //a(-->a.(
		{
			for (j = nstr; j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i + 1] = '.';
			nstr++;

		}
		if ((str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122) && str[i - 1] == ')')  // )a -->).a
		{
			for (j = nstr; j > i; j--)
			{
				str[j] = str[j - 1];
			}
			str[i] = '.';
			nstr++;

		}
		if (str[i] == ')'&&str[i + 1] == '(')  //  )( --> ).(
		{
			for (j = nstr; j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i + 1] = '.';
			nstr++;
		}
		if (str[i] == 39 && (str[i + 1] >= 65 && str[i + 1] <= 90 || str[i + 1] >= 97 && str[i + 1] <= 122))   //  'a--> ' . a              //39--> '
		{
			for (j = nstr; j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i + 1] = '.';
			nstr++;

		}
		if (str[i] == 39 && str[i + 1] == '(')   //  '( --> ' . (              //39--> '
		{
			for (j = nstr; j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i + 1] = '.';
			nstr++;
		}
	}



}


void calculate(int x[], char str[], char var[], int &nstr, int &nvar,int num[])
{
	int i,j,ind1,ind2,c;

	for (i = 0; i < 1000; i++)
	{
		num[i] = 0;
	}

	//邏輯計算系統
//套值
	for (i = 0; i < nstr; i++)
	{
		if (str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122)
		{
			for (j = 0; j < nvar; j++)
			{
				if (var[j] == str[i])
				{
					num[i] = x[j];
				}
			}
		}
	}


	//計算
	while (str[0] == '(')
	{
		

		ind1 = 0;
		ind2 = 0;
		for (i = 0;ind2==0; i++)
		{
			if (str[i] == '(')ind1 = i;
			if (str[i] == ')')ind2 = i;
		}
		//printf("-->%d %d\n",ind1,ind2);

		c = 0;
		while (c == 0)
		{
			c = 1;
			for (i = ind1; i < nstr&& str[i] != ')'; i++)
			{
				if (str[i] == 39 && str[i - 1] != ')')  //not  '
				{
					num[i - 1] = 1 - num[i - 1];
				//printf("->%d %d  not \n", i, num[i - 1]);
					str[i - 1] = -1;
					for (j = i; j < nstr; j++)
					{
						str[j] = str[j + 1];
						num[j] = num[j + 1];
					}
					nstr--;
					c = 0;
					i = ind1;
				}
			}
		}


		c = 0;
		while (c == 0)
		{
			c = 1;
			for (i = ind1; i < nstr&& str[i] != ')'; i++)
			{
				if (str[i] == '.')  //and  
				{
					num[i - 1] = num[i - 1] && num[i + 1];
					//printf("->%d %d  and \n", i, num[i - 1]);
					str[i - 1] = -1;
					for (j = i; j < nstr; j++)
					{
						str[j] = str[j + 2];
						num[j] = num[j + 2];
					}
					nstr = nstr - 2;
					c = 0;
					i = ind1;
				}
			}
		}


		c = 0;
		while (c == 0)
		{
			c = 1;
			for (i = ind1; i < nstr&& str[i] != ')'; i++)
			{
				if (str[i] == '+')  //or 
				{
					num[i - 1] = num[i - 1] || num[i + 1];
				//printf("->%d %d  or \n", i, num[i - 1]);
					str[i - 1] = -1;
					for (j = i; j < nstr; j++)
					{
						str[j] = str[j + 2];
						num[j] = num[j + 2];
					}
					nstr = nstr - 2;
					c = 0;
					i = ind1;
				}
			}
		}


		//(a) --> a
		//printf("->%d %d  () \n", ind1, num[ind1+1]);
		num[ind1] = num[ind1 + 1];
		str[ind1] = -1;
		for (j = ind1 + 1; j < nstr; j++)
		{
			str[j] = str[j + 2];
			num[j] = num[j + 2];
		}
		nstr = nstr - 2;

	}

	//printf("-->%d\n ", num[0]);

	


}

int main(void)
{
	char str[1000],var[1000],oper[1000];  //字串、變數     str->讀取到的算試    var->讀取到的變數  
	int product[1000],x[1000],num[1000];  //乘積      x->2進位窮舉           num->儲存的數值(進行運算)
	int i,j,k,nstr=0,nvar=0,NSTR;    //str->str的長度    nvar->var的長度
	char pos_output[1000],sop_output[1000];
	int output_count ;
	
	printf("範例:aa+a'b'+(a+c)af\n");
	printf("說明:\n");
	printf("a\' 是not\n");
	printf("aa 或 a.a 是AND\n");
	printf("a+a 是OR\n"); 
	printf("請輸入布林代數: ");
	

	for (i = 0; i < 1000; i++)
	{
		str[i] = -1;
		var[i] = -1;
		product[i] = -1;
		x[i] = 0;
		num[i] = 0;
		oper[i] = -1;
		pos_output[i] = '$';
		sop_output[i] = '$';
	}

	//a.a+a.b'+(a+c).a
	
	gets(str);

	for (i = 0; str[i] != 0; i++)
	{
		printf("%d %c %d\n", i, str[i], str[i]);
	}
	nstr = i;

	printf("\n");


	translate(str,  var, nstr, nvar);

	printf("\n");
	for (i = 0; i < nstr; i++)
		printf("%d %c\n", i, str[i]);
	printf("\n");





	NSTR = nstr;
	for (i = 0; i < nstr; i++)  //暫存
		oper[i] = str[i];
	
	/*
	x[0] = 1;
	x[1] = 1;
	nstr = NSTR;
	for(i=0;i<nstr;i++)
	str[i] = oper[i];
	calculate(x, str, var, nstr, nvar, num);

	x[0] = 1;
	x[1] = 0;
	nstr = NSTR;
	for (i = 0; i < nstr; i++)
		str[i] = oper[i];
	calculate(x, str, var, nstr, nvar, num);

	x[0] = 0;
	x[1] = 1;
	nstr = NSTR;
	for (i = 0; i < nstr; i++)
		str[i] = oper[i];
	calculate(x, str, var, nstr, nvar, num);

	x[0] = 0;
	x[1] = 0;
	nstr = NSTR;
	for (i = 0; i < nstr; i++)
		str[i] = oper[i];
	calculate(x, str, var, nstr, nvar, num);

	*/
	
	
	for (i = 0; i < nvar; i++)
	{
		printf("%c ", var[i]);
	}
	printf("ans");
	printf("\n");
	for (i = 0; i < pow(2, nvar); i++)   //窮舉法
	{
		for (j = 0; j < nvar; j++)
		{
			printf("%d ", x[j]);
		}
		nstr = NSTR;
		for (k = 0; k< nstr; k++)
			str[k] = oper[k];
		calculate(x, str, var, nstr, nvar, num);
		printf("%d ", num[0]);

		printf("\n");


		for (j = 0; j < pow(2, nvar); j++)
		{
			if (j == 0)x[j]++;
			x[j + 1] = x[j + 1] + x[j] / 2;
			x[j] = x[j] % 2;
		}
		//計算窮舉
	}
	printf("\n");
	

	//SOP
	printf("SOP:\n");
	output_count = 0;
	for (i = 0; i < pow(2, nvar); i++)   //窮舉法
	{

		nstr = NSTR;
		for (k = 0; k < nstr; k++)
			str[k] = oper[k];
		calculate(x, str, var, nstr, nvar, num);

		if (num[0] == 1)
		{
			for (j = 0; j < nvar; j++)
			{
				//printf("%c", var[j]);
				sop_output[output_count] = var[j];
				output_count++;

				if (x[j] == 0) {
					//printf("'");
					sop_output[output_count] = '\'';
					output_count++;
				}
			}
			//printf("+");
			sop_output[output_count] = '+';
			output_count++;
		}


		for (j = 0; j < pow(2, nvar); j++)
		{
			if (j == 0)x[j]++;
			x[j + 1] = x[j + 1] + x[j] / 2;
			x[j] = x[j] % 2;
		}
		//計算窮舉
	}
	if (output_count > 0) {
		output_count--;
	}
	sop_output[output_count] = '$';
	for (i = 0; i < output_count; i++) {
		printf("%c", sop_output[i]);
	}
	printf("\n");


	
	
	//POS
	printf("\nPOS:\n");
	output_count = 0;
	for (i = 0; i < pow(2, nvar); i++)   //窮舉法
	{

		nstr = NSTR;
		for (k = 0; k < nstr; k++)
			str[k] = oper[k];
		calculate(x, str, var, nstr, nvar, num);

		if (num[0] == 0)
		{
			//printf("(");
			pos_output[output_count] = '(';
			output_count++;

			for (j = 0; j < nvar; j++)
			{
				//printf("%c", var[j]);
				pos_output[output_count] = var[j];
				output_count++;

				if (x[j] == 1) { //printf("'"); 
					pos_output[output_count] = '\'';
					output_count++;
				}
				//printf("+");
				pos_output[output_count] = '+';
				output_count++;
			}
			output_count--;
			//printf(")");
			pos_output[output_count] = ')';
			output_count++;
			//printf(".");
			pos_output[output_count] = '.';
			output_count++;
		}
		
		for (j = 0; j < pow(2, nvar); j++)
		{
			if (j == 0)x[j]++;
			x[j + 1] = x[j + 1] + x[j] / 2;
			x[j] = x[j] % 2;
		}
		//計算窮舉
	}
	if (output_count > 0) {
		output_count--;
	}
	pos_output[output_count] = '$';
	for (i = 0; i < output_count; i++) {
		printf("%c", pos_output[i]);
	}
	printf("\n");



	//列舉布林代數 & 計算相符的 


	system("PAUSE");
	return 0;
}




