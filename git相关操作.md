


查看远程仓库
查看远程仓库:git remote
查看仓库地址:git remote -v
例:
git remote -v
origin https://git.oschina.net/lianshou/test.git (fetch)
origin https://git.oschina.net/lianshou/test.git (push)
删除远程库
命令:git remote remove <远程库名>
示例:git remote remove origin
5.1 添加远程库
命令:git remote add <远程库名> <远程库地址>
示例:
git remote add origin https://git.oschina.net/lianshou/test.git
注: 远程库名一般叫origin,但并非强制,你可以自己起名.
例:
git remote add online https://git.oschina.net/lianshou/test.git
5.2 修改远程库名称
git remote rename <旧名称> <新名称>
例:
git remote rename online oschina
公钥登陆
我们push本地仓库到远程时,总要输入用户名/密码,这很不方便.
配置公钥,可以避免频繁输用户名/密码的麻烦.

1. 配置ssh格式的远程仓库地址
  git remote add 远程仓库名 远程仓库地址
  例:
  git remote add gitaddr git@git.oschina.net:lianshou/test.git
2. 创建ssh key
  ssh-keygen -t rsa -C "youremail@example.com",把邮件地址换成你自己的邮件地址,一直回车,不用输入密码.完成后,可以在用户主目录里找
  到.ssh目录,内有id_rsa和id_rsa.pub两个文件. id_rsa是私钥,id_rsa.pub是公钥.
  这两把钥匙是成对的,可以让分别持有私钥和公钥的双方相互认识.
3. 把公钥放在服务器
  用记事本打开id_rsa.pub,复制公钥内容.
  登陆git.oschina.net,如下图,填入公钥并保存 




3.4 版本切换
我们针对ver.txt,连续修改4次,形成4个版本,练习版本切换.
one line
second line
third line
four line
git reflog 查看版本变化
$ git reflog
5d5df85 HEAD@{0}: commit: four
6207e59 HEAD@{1}: commit: three
70110b9 HEAD@{2}: commit: two
bc65223 HEAD@{3}: commit (initial): one
HEAD指向当前版本5d5df86,
切换为head的前1版本,git reset --hard HEAD^
切换为head的前2版本,git reset --hard HEAD^^
切换为head的前100版本,git reset --hard HEAD~100
实例: $ git reset --hard HEAD^^
HEAD is now at 70110b9 two
此时,查看ver.txt的内容变为:
one line
two line
也可以利用版本号来切换,例
$ git reset --hard 6207e59
HEAD is now at 6207e59 three
注意:版本号不用写那么长,能要能保证不与其他版本号重复就行.
例git reset --hard 6207 how to delete branch
git branch -d +分支







git 常见问题

windows中的换行符为 CRLF， 而在linux下的换行符为LF，所以在执行add . 时出现提示，解决办法：



1. $ rm -rf .git  // 删除.git  
2. $ git config --global core.autocrlf false  //禁用自动转换    

然后重新执行：



1. $ git init    
2. $ git add .  