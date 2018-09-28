= 登録機能の実装をしよう
この章ではCloud Firestoreへデータの登録を行う機能を作成します。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter9}

== 登録機能作成

Cloud Firestoreにデータを保存するために次のコードを追加します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_registration1][main.dart]{
class _MyInputFormState extends State<InputForm> {

  @override
  Widget build(BuildContext context) {
    /*---------- Add Start ----------*/
    DocumentReference _mainReference;
    _mainReference = Firestore.instance.collection('kasikari-memo').document();
    /*----------- Add End -----------*/

    return Scaffold(
      appBar: AppBar(
        title: const Text('かしかり入力'),
        actions: <Widget>[
          IconButton(
            icon: Icon(Icons.save),
            onPressed: () {
              print("保存ボタンを押しました");
              /*---------- Add Start ----------*/
              if (_formKey.currentState.validate()) {
                _formKey.currentState.save();
                _mainReference.setData(
                  {
                    'borrowOrLend': _data.borrowOrLend,
                    'user': _data.user,
                    'stuff': _data.stuff,
                    'date': _data.date
                  }
                );
                Navigator.pop(context);
              }
              /*----------- Add End -----------*/
            }
          ),
          IconButton(
            ...
          ),
        ],
      ),
      ...
    )
  }
}
//}

=== 登録機能作成説明

Cloud Firestoreにデータを登録するために、@<code>{Firestore.instance.collection('コレクション名').document();}
を使用し、インスタンスを生成します。

保存ボタンを選択後、@<code>{_formKey}を使用し、前の章で実装した入力チェックを行います。

 * @<code>{_formKey.currentState.validate()}で前の章で実装した@<code>{validator}を呼び出します。
 * @<code>{_formKey.currentState.save()}で前の章で実装した@<code>{onSaved}を呼び出します。

入力チェックを行い、問題なければ、@<code>{_mainReference.setData()}を使用し、Cloud Firestoreへデータの登録を行います。

「"キー":"値"」の形式で、Cloud Firestoreへデータの登録を行い、４つのデータを保存します。

@<code>{Navigator.pop}を利用して、元の一覧画面に戻ります。
