= 削除機能の実装
この章では、登録したデータの削除する機能の実装を行います。
前章にてドキュメントIDを参照する機能を実装したので、それを利用し、登録してあるデータの削除を行います。

== コードの説明
//list[main_delete1][main.dart]{

class _MyInputFormState extends State<InputForm> {
  bool deleteFlg;
  ...
  @override
  Widget build(BuildContext context) {
    if (this.widget.docs != null) {
      if(lendorrent_Flg == 0 && widget.docs['lendorrent'].toString() == "lend"){
        lendorrent = "lend";
        lendorrent_Flg = 1;
      }
      _data.user = widget.docs['name'];
      _data.loan = widget.docs['loan'];
      print(date);
      if(change_Flg == 0) {
        date = widget.docs['date'];
      }
      _mainReference = Firestore.instance.collection('promise').document(widget.docs.documentID);
      deleteFlg = true;
    } else {
      _data.lendorrent = "";
      _data.user = "";
      _data.loan = "";
      _mainReference = Firestore.instance.collection('promise').document();
      deleteFlg = false;
    }

    titleSection = Scaffold(
      appBar: AppBar(
        title: const Text('かしかりめも'),
        actions: <Widget>[
        ...
        IconButton(
          icon: Icon(Icons.delete),
          onPressed: !deleteFlg? null:() {
            _mainReference.delete();
            Navigator.pop(context);
            },
        )
        ],
    ),
    ...
  }
}
//}

"_MyInputFormState"実行時に"deleteFlg"の初期値の設定を行います。
引数の"docs"が"null"でなければ、編集時なので"deleteFlg"に"true",
"null"であれば、新規登録なので、"false"を代入します。

"IconButton"内では"deleteFlg"を利用し、編集時のみ機能を有効化し、実際の削除は、
”Firestore.instance.collection('コレクション名').document('ドキュメントID').delete()”
で実行しています。

この状態で、アプリを実行してみましょう。
今までに登録したデータの一覧が表示されるので、削除したいデータをタップします。
タップすると、編集画面に遷移するので、画面上部にある、削除アイコン（ゴミ箱アイコン）をタップします。
タップ後、一覧画面が表示されるので、削除したものが表示されてないことを確認してみましょう。
