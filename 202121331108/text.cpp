void textsStatement( string file )    // 读取text文本的内容并使用动态规划进行查重
{
    ifstream infile; 
    infile.open( file.data() );   //将文件流对象与文件连接起来 
    assert( infile.is_open() );   //若失败,则输出错误消息,并终止程序运行 
 
    char nowcur;
	string tempStatement="";
	Statement temp;
	int num1 = 0;
 
    infile >> noskipws;
 
    while ( !infile.eof() )
    {
        infile>>nowcur;
 
		if((( nowcur >='a' )&&( nowcur <='z' ))||(( nowcur >='A' )&&( nowcur <='Z' )))
		{
			tempStatement += nowcur;
 
		}else if(( nowcur =='.' )||( nowcur =='?' )||( nowcur =='!' ))   //完成一个句子的读取，进行动态规划匹配查重
		{
			transform(tempStatement.begin(), tempStatement.end(), tempStatement.begin(), ::tolower);
			temp.nums = num1+1;            // 把当前读取到的test句子的单词个数存下
			temp.statement = tempStatement;  // 把当前读取到的test句子存下 
			num1 = 0;
			tempStatement = "";
 
			for(int i=0;i<orgnums-1;i++ )   //分别与org中的每一句进行对比
			{
				string t;
				int n = 0;
				int k,j;
 
				for(istringstream is(temp.statement); is>>t;) {   //存储把test的句子分割出来的单词
					str1[n++] = t;
				}
 
				n = 0;
				for(istringstream is1(orgStatement[i].statement); is1>>t;) {   //存储把org的句子分割出来的单词
					str2[n++] = t;
				}
 
				for( k=0;k<temp.nums;k++)   //test当前句子的个数
				{
					for( j=0;j<orgStatement[i].nums;j++)  //与org文件的句子的单词分别进行对比
					{
						if(str1[k]==str2[j])
							words[k][j] = 1;
						else
							words[k][j] = 0;
					}
				}
				
				for(k=0; k<temp.nums; k++)
				{  
					grade[k][0] = max(grade[k-1][0]-0.5, words[k][0]-0.5*(k-1) );
				} 
				for(k=0; k<orgStatement[i].nums; k++)
				{  
					grade[0][k] = max(grade[0][k-1]-0.5, words[0][k]-0.5*(k-1) );
				}
				for(k=1;k<temp.nums;k++)
				{
					for(j=1;j<orgStatement[i].nums;j++)
					{
						grade[k][j] = maxs( grade[k-1][j]-0.5, grade[k][j-1]-0.5, grade[k-1][j-1]+words[k][j] );
					}
				}
 
				int sum = grade[temp.nums-1][orgStatement[i].nums-1];
				
				if(allstorage[textnums].snums < sum)
				{
					allstorage[textnums].org = orgStatement[i].statement;
					allstorage[textnums].snums = sum;
					allstorage[textnums].tnums = temp.nums;
					allstorage[textnums].text = temp.statement;
				}
			}
			textnums++;   //test文件的句子的个数
 
		}else  //匹配到空格
		{
			if( tempStatement=="" )
			{
				continue;
			}
			else if(tempStatement[tempStatement.size()==1?1:tempStatement.size()-1] != ' ') //匹配到空格，当前句末不为空格，添加空格
			{
				tempStatement += " ";
				num1 += 1;
			}
		}
    }
    infile.close();             //关闭文件输入流 
}
