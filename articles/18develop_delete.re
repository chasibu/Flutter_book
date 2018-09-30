= 削除機能の実装をしよう

この章では、登録したデータの削除する機能の実装を行います。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter11}

== 削除機能の作成

_MyInputFormStateクラスに削除機能を追加します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_delete1][main.dart]{
  class _MyInputFormState extends State<InputForm> {
  ...
    @override
    Widget build(BuildContext context) {
      DocumentReference _mainReference;
      _mainReference = Firestore.instance.collection('kasikari-memo').document();
      /*---------- Add Start ----------*/
      bool deleteFlg = false;
      /*----------- Add End -----------*/
      if (widget.document != null) {
        if(_data.user == null && _data.stuff == null) {
          _data.borrowOrLend = widget.document['borrowOrLend'];
          _data.user = widget.document['user'];
          _data.stuff = widget.document['stuff'];
          _data.date = widget.document['date'];
        }
        _mainReference = Firestore.instance.collection('kasikari-memo').
                          document(widget.document.documentID);
        /*---------- Add Start ----------*/
        deleteFlg = true;
        /*----------- Add End -----------*/
        }
        return Scaffold(
          appBar: AppBar(
            title: const Text('かしかり入力'),
            actions: <Widget>[
            IconButton(
              icon: Icon(Icons.save),
              onPressed: () {
                ...
              }
            ),
            IconButton(
              icon: Icon(Icons.delete),
              /*---------- Add Start ----------*/
              onPressed: !deleteFlg? null:() {
                print("削除ボタンを押しました");
                _mainReference.delete();
                Navigator.pop(context);
              },
              /*----------- Add End -----------*/
            )
            ],
          ),
        )
      }
  ...
}
//}


次の画像のように実際に登録してあるデータを削除してみましょう。

//image[delete][登録データの削除][scale=0.9]{
//}

=== 削除機能の解説

@<code>{!deleteFlg? null:() }このコードで入力画面を表示するときに削除ボタンの有効化・無効化を判定しています。
画面上部にある削除ボタンを編集のときは有効化、新規作成のときには無効化します。

編集時には@<code>{_mainReference.delete()}を利用して、データ削除を行います。

これで削除機能の実装は完了です。
