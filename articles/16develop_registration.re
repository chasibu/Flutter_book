= 登録機能の実装をしよう
この章ではCloud Firestoreへデータの登録を行う機能を作成します。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter9}

== 登録機能作成

Cloud Firestoreにデータを保存するために次のコードを追加します。

この次の項目の「入力チェック機能」まで行ってから動作確認をします。

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

保存ボタンを選択後、@<code>{_formKey}を使用し、次の項目で実装する入力チェックを行います。

 * @<code>{_formKey.currentState.validate()}で次の項目で実装する@<code>{validator}を呼び出します。
 * @<code>{_formKey.currentState.save()}で次の項目で実装する@<code>{onSaved}を呼び出します。

入力チェックを行い、問題なければ、@<code>{_mainReference.setData()}を使用し、Cloud Firestoreへデータの登録を行います。

「"キー":"値"」の形式で、Cloud Firestoreへデータの登録を行い、４つのデータを保存します。

@<code>{Navigator.pop}を利用して、元の一覧画面に戻ります。

== 入力チェック機能

テキストフォームで入力された文字のチェック機能を作成します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input4][main.dart]{

class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        ...
      ),
      body: SafeArea(
        child:
          Form(
              key: _formKey,
              child: ListView(
                padding: const EdgeInsets.all(20.0),
                children: <Widget>[
                ...

                TextFormField(
                    decoration: const InputDecoration(
                      icon: const Icon(Icons.person),
                      hintText: '相手の名前',
                      labelText: 'Name',
                    ),
                    /*---------- Add Start ----------*/
                    onSaved: (String value) {
                      _data.user = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '名前は必須入力項目です';
                      }
                    },
                    initialValue: _data.user,
                    /*----------- Add End -----------*/
                ),

                TextFormField(
                  decoration: const InputDecoration(
                      icon: const Icon(Icons.business_center),
                      hintText: '借りたもの、貸したもの',
                      labelText: 'loan',
                    ),
                    /*---------- Add Start ----------*/
                    onSaved: (String value) {
                      _data.stuff = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '借りたもの、貸したものは必須入力項目です';
                      }
                    },
                    initialValue: _data.stuff,
                    /*----------- Add End -----------*/
                  ),
                  ...
              ],
            ),
          ),
      ),
    );
  }
}
//}

空データのときに保存ボタンを押してみましょう。次のような画面になります。

//image[verify][入力チェック機能][scale=0.7]{
//}

ここまで来たら文字を入力して上の保存ボタンを押すと、
その入力データをCloud Firestoreに保存し、そのデータを一覧画面で確認できるはずなのでぜひ試してみてください。

=== 入力チェック機能説明

@<code>{TextFormField}に対して、入力チェック機能を実装していきます。

 * @<code>{validator:}で入力欄が空欄のときにエラー文を返すように設定します。
 * @<code>{onSaved:}で@<code>{_data}の各プロパティに対して、値の代入を行ないます。

 @<code>{initialValue:}で初期値を設定します。

これで登録処理機能の実装は完了です。
