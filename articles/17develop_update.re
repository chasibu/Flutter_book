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

  Future <Null> _selectTime(BuildContext context) async {
    final DateTime picked = await showDatePicker(
        context: context,
        initialDate: date,
        firstDate: new DateTime(2018),
        lastDate: new DateTime(2020)
    );

    if(picked != null && picked != date){
      setState(() {
        date = picked;
        change_Flg = 1;
        print(date);
      });
    }
  }


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

"InputForm"が引数を受けれるように"InputForm"クラス内でコンストラクタを定義します。

次に”_MyInputFormState”内では、"InputForm"内の引数によって、"_data"に代入する値を変更しています。
”Null”である場合には、全てのデータに”空欄”を代入、データがある場合にはドキュメントIDを参照して
データを代入しています。

=== lendorrent_Flgについて
貸し借りの表記を今回”RadioListTile”を使用して実現しているのですが、"lendorrent"に対して変数を直接代入すると
ラジオボタンが正常に動作しなくなります。そのため、後から編集するために、もともと"lend"が代入されているのか
"rent"が代入されているのかを判断し、"lendorrent"に対して実値を代入しています。

=== change_Flgについて
こちらは、日時を入力する為のフラグになります。”showDatePicker”を使用し、データを入力すると、入力後に
"build()"内の処理が実行されてしまいます。その為、新規登録した時の値をそのまま"build()"内で代入すると
更新しようとした時に、新規登録した時の値で上書きされてしまいます。
そこで、"change_Flg"を利用し、更新時に初期登録時の値で上書きしないようにしています。
また、"_selectTime()"内で、時刻データ登録時に”change_Flg = 1;”と追記しております。

ここまでの記述が完了したら、一度アプリを立ち上げてみましょう。
一覧画面が表示され、”へんしゅうボタン”を選択すると、新規登録画面に元々登録した値が代入された状態で
表示されます。
