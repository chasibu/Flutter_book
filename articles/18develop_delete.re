= 削除機能の実装
この章では、登録したデータの削除する機能の実装を行います。
前章にてドキュメントIDを参照する機能を実装したので、それを利用し、登録してあるデータの削除を行います。

この章を完了すると下記のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter12}

== deleteflagの用意

//list[main_delete1][main.dart]{
  class _MyInputFormState extends State<InputForm> {
  ...
    @override
    Widget build(BuildContext context) {
      DocumentReference _mainReference;
      //add
      bool deleteFlg = false;
      if (widget.document != null) {
        if(_data.user == null && _data.stuff == null) {
          _data.borrowOrLend = widget.document['borrowOrLend'];
          _data.user = widget.document['user'];
          _data.stuff = widget.document['stuff'];
          _data.date = widget.document['date'];
        }
        _mainReference =_mainReference = Firestore.instance.collection('kasikari-memo').document(widget.document.documentID);
        /*---------- Add Start ----------*/
        deleteFlg = true;
        /*----------- Add End -----------*/
        } else {
          _mainReference = _mainReference = Firestore.instance.collection('kasikari-memo').document();
        }
      }
  ...
}
//}
@<code>{build()}の中に@<code>{deleteFlg}を用意します。
編集画面への遷移のように前画面から何かデータを引き継ぐ場合には、@<code>{deleteFlg}にtrueにします。
次に実装するのですが、@<code>{true}の場合には、画面上部にある削除ボタンを有効化、@<code>{false}の場合には無効化するのに
使用します。

== 削除の実施

//list[main_delete2][main.dart]{
class _MyInputFormState extends State<InputForm> {
    ...
    @override
    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
          title: const Text('かしかり入力'),
          actions: <Widget>[
          IconButton(
            icon: Icon(Icons.save),
            onPressed: () {
              print("保存ボタンを押しました");
              if (_formKey.currentState.validate()) {
                _formKey.currentState.save();
                _mainReference.setData(
                {
                  'borrowOrLend': _data.borrowOrLend,
                  'user': _data.user,
                  'stuff': _data.stuff,
                  'date': _data.date
                });
                Navigator.pop(context);
              }
            }
          ),
          IconButton(
            icon: Icon(Icons.delete),
            //add-start
            onPressed: !deleteFlg? null:() {
              print("削除ボタンを押しました");
              _mainReference.delete();
            },
            //add-end
          )
          ],
        ),
      )
    }
  ...
}
//}

@<code>{deleteFlg}が@<code>{true}の場合には、削除機能が有効になり、
@<code>{_mainReference.delete()}を利用して、データ削除を行います。

ここまで実装すると、削除機能が有効になります。
次の画像のように実際に登録してあるデータを削除してみましょう。

//image[list_before][一覧画面(削除前)][scale=0.6]{
//}

//image[update][編集画面][scale=0.6]{
//}

//image[list_after][一覧画面(削除後)][scale=0.6]{
//}
