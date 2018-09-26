= 新規登録画面への遷移
この章では、先ほど作成した一覧画面から、新規登録画面を表示する機能を実装します。
具体的には画面右下にある、ボタンを選択することで新規登録画面を開くようにします。

この章を完了すると下記のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter9}

== 画面遷移のメソッドについて
Flutterでは画面遷移を行う場合は、「Navigate」クラスを使用します。
クラス内に画面遷移に関するメソッドはいくつかあるのですが、今回は「push」と「pop」を利用します。
pushは特定の画面に遷移するときに使用し、遷移先の画面から元の画面に戻るときはpopを使用します。


== コードの説明
今回は、「_MyList」クラスの「_buildListItem()」と「_MyInputFormState」クラスの「build()」
の中しか触らない為、そこだけ抜粋して記載します。

//list[main_transition1][main.dart]{
class _MyList extends State<_List> {
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: appbar(
        ...
        ),
      body: Padding(
        ...
      ),

  floatingActionButton: new FloatingActionButton(
    child: new Icon(Icons.check),
    onPressed: () {
      print("新規作成ボタンを押しました");
      Navigator.push(
        context,
        MaterialPageRoute(
            settings: const RouteSettings(name: "/new"),
            builder: (BuildContext context) => new InputForm()
        ),
      );
    }),
    );
  }
}
//}

「floatingActionButton」の「onPressed: ()」に「Navigator.push」を追加しています。
「Navigator.push」内では「BuildContext」クラスと「Route」クラスを記載する必要があり、ここでは
「context」と「MaterialPageRoute」を定義しています。
//comment{
  ここの説明をもっと記載する。
//}
「MaterialPageRoute」内で遷移先のページのルートと呼び出すクラスを決定します。
今回は、ルートを”/new”とし、呼び出すクラスを「InputForm()」としています。

//list[main_transition2][main.dart]{
class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
  ・・・
  @override
 Widget build(BuildContext context) {
   Widget titleSection;
       titleSection = Scaffold(
         appBar: AppBar(
           title: const Text('かしかりめも'),
           actions: <Widget>[
             // action button
             IconButton(
               icon: Icon(Icons.save),
               onPressed: () {
                 print("保存ボタンを押しました");
                 Navigator.pop(context);
               }
             ),
             ・・・
             ),
          );
return titleSection;
}
}
//}

「_MyInputFormState」クラスの「build」内の保存ボタン用の「IconButton」に
「Navigator.pop(context)」を追加しました。
この状態でアプリを起動すると、一覧画面から新規登録画面、新規登録画面から
一覧画面への遷移が可能になります。
