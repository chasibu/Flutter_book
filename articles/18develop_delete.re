= 削除機能の実装
この章では、登録したデータの削除する機能の実装を行います。
前章にてドキュメントIDを参照する機能を実装したので、それを利用し、登録してあるデータの削除を行います。
変更を加えるのは、”_MyInputFormState”内の"Scaffold"にある削除のアイコンボタンになります。



== コードの説明
//list[main_delete1][main.dart]{



//}
"deleteFlg"を利用し、編集時のみ機能を有効化し、実際の削除は、
”Firestore.instance.collection('コレクション名').document('ドキュメントID').delete()”
で実行しています。

この状態で、アプリを実行してみましょう。
今までに登録したデータの一覧が表示されるので、削除したいデータをタップします。
タップすると、編集画面に遷移するので、画面上部にある、削除アイコン（ゴミ箱アイコン）をタップします。
タップ後、一覧画面が表示されるので、削除したものが表示されてないことを確認してみて下さい。
