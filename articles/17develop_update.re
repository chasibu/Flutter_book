= 編集機能の実装
この章では登録してあるデータを呼び出し、再び保存する編集機能の実装を行います。

== 登録データの呼び出しについて
登録データを呼び出すには「Firestore.instance.collection(”コレクション名”).document(”ドキュメントID”)」
を使用します。
全体的な動きは次のとおりになります。

1. 一覧画面から編集したいデータを選択。その際に、対象のデータのドキュメントIDを表示画面先に渡す。
2. 受け取ったドキュメントIDを元にFirestoreからデータを取得。
3. 紐づいているキーの値を元に入力フォームに値を入力。

== コードの説明
今回は、一覧画面側（_buildListItem()）と編集画面側（_MyInputFormState()）でコードの編集を行います。
まずは、一覧画面から編集画面に対してドキュメントIDを渡す箇所についてです。

//list[main_update1][main.dart]{
class _MyList extends State<_List> {

  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("一覧"),
      ),
      body: Padding(
      ...
      ),
      floatingActionButton: new FloatingActionButton(
          child: new Icon(Icons.check),
          onPressed: () {
            Navigator.push(
              context,
              MaterialPageRoute(
                  settings: const RouteSettings(name: "/new"),
                  builder: (BuildContext context) => new InputForm(null)
              ),
            );
          }),
    );
  }

  Widget _buildListItem(BuildContext context, DocumentSnapshot document){
    return new Card(
      child: new Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            ListTile(
              ...
            ),
            new ButtonTheme.bar(
                child: new ButtonBar(
                  children: <Widget>[
                    new FlatButton(
                      child: const Text("へんしゅう"),
                      onPressed: ()
                        {
                          Navigator.push(
                          context,
                          MaterialPageRoute(
                            settings: const RouteSettings(name: "/new"),
                            builder: (BuildContext context) => new InputForm(document)
                          ),
                          );
                        },
                        ),
                  ],
                )
            ),
          ]
      ),
    );
  }
}
//}
MaterialPageRouteを使用して編集ボタンを押した後のルーティングの設定をしています。
”document”を引数として、”InputForm()”を呼び出していますが、今のコードでは"InputForm()"は引数を
持たない設定になっているので、エラーが表示されると思いますが、それは次の箇所で説明します。

また、順番が前後しますが、”InputForm()”の引数を一つ加える事で”floatingActionButton:”の中の
”InputForm()”もエラー文が発生するため、先に引数に(null)を加える変更をしておきます。

それでは、"InputForm()"のコードを次に記載します。

//list[main_update2][main.dart]{

class InputForm extends StatefulWidget {

  InputForm(this.docs);
  final DocumentSnapshot docs;

  @override
  _MyInputFormState createState() => new _MyInputFormState();
}

...

class _MyInputFormState extends State<InputForm> {

  final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
  _formData _data = new _formData();
  String lendorrent = "rent";
  DateTime date = new DateTime.now();
  var change_Flg = 0;
  var lendorrent_Flg = 0;

　...

  Widget build(BuildContext context) {
    var _mainReference;
    if (this.widget.docs != null) {
      if(lendorrent_Flg == 0 && widget.docs['lendorrent'].toString() == "lend"){
        lendorrent = "lend";
        lendorrent_Flg = 1;
      }
      _data.user = widget.docs['name'];
      _data.loan = widget.docs['loan'];
      if(change_Flg == 0) {
        date = widget.docs['date'];
      }
      _mainReference = Firestore.instance.collection('promise').document(widget.docs.documentID);
      } else {
        _data.lendorrent = "";
        _data.user = "";
        _data.loan = "";
        _mainReference = Firestore.instance.collection('promise').document();
      }
    }
    ...
}
//}

"InputForm"に引数を受けれるように
