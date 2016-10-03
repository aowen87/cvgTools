
void AVLTest()
{

    //Gene compression testing 
    cerr << "Gene compression testing: " << endl;
    TranscriptLine *t1 = new TranscriptLine("supercontig12.1", "gene3", "t", "", "", "", 'r', 8, 19, '+');
    TranscriptLine *t2 = new TranscriptLine("supercontig12.2", "gene5", "t", "", "", "", 'r', 65, 80, '+');
    TranscriptLine *t3 = new TranscriptLine("supercontig12.1", "gene3", "t", "", "", "", 'r', 0, 10, '+');
    TranscriptLine *t4 = new TranscriptLine("supercontig12.3", "gene8", "t", "", "", "", 'r', 34, 36, '+');
    TranscriptLine *t5 = new TranscriptLine("supercontig12.1", "gene2", "t", "", "", "", 'r', 22, 30, '+');
    TranscriptLine *t6 = new TranscriptLine("supercontig12.2", "gene5", "t", "", "", "", 'r', 50, 91, '+');
    TranscriptLine *t7 = new TranscriptLine("supercontig12.1", "gene1", "t", "", "", "", 'r', 22, 35, '+');
    TranscriptLine *t8 = new TranscriptLine("supercontig12.3", "gene6", "t", "", "", "", 'r', 65, 73, '+');
    TranscriptLine *t9 = new TranscriptLine("supercontig12.3", "gene8", "t", "", "", "", 'r', 37, 54, '+');
    TranscriptLine *t10 = new TranscriptLine("supercontig12.3", "gene6", "t", "", "", "", 'r', 72, 80, '+');

    TranscriptLine *d1 = new TranscriptLine("supercontig12.3", "gene6", "t", "", "", "", 'r', 72, 80, '+');
    AVLTree tree('g');
    tree.Insert(t1);
    tree.Insert(t2);
    tree.Insert(t3);
    tree.Insert(t4);
    tree.Insert(t5);
    tree.Insert(t6);
    tree.Insert(t7);
    tree.Insert(t8);
    tree.Insert(t9);
    tree.Insert(t10);
    tree.InorderTraverse();
    tree.Delete(d1);
    cerr << "\n" << endl;
    tree.InorderTraverse();

    cerr << "\n" << endl;
    TranscriptLine *t11 = new TranscriptLine("supercontig12.1", "gene3", "t", "", "", "", 'r', 8, 19, '+');
    TranscriptLine *t21 = new TranscriptLine("supercontig12.2", "gene5", "t", "", "", "", 'r', 65, 80, '+');
    TranscriptLine *t31 = new TranscriptLine("supercontig12.1", "gene4", "t", "", "", "", 'r', 0, 10, '+');
    TranscriptLine *t41 = new TranscriptLine("supercontig12.3", "gene8", "t", "", "", "", 'r', 34, 36, '+');
    TranscriptLine *t51 = new TranscriptLine("supercontig12.1", "gene2", "t", "", "", "", 'r', 22, 30, '+');
    TranscriptLine *t61 = new TranscriptLine("supercontig12.2", "gene9", "t", "", "", "", 'r', 50, 91, '+');
    TranscriptLine *t71 = new TranscriptLine("supercontig12.1", "gene1", "t", "", "", "", 'r', 22, 35, '+');
    TranscriptLine *t81 = new TranscriptLine("supercontig12.3", "gene7", "t", "", "", "", 'r', 65, 73, '+');
    TranscriptLine *t91 = new TranscriptLine("supercontig12.3", "gene8", "t", "", "", "", 'r', 37, 54, '+');
    TranscriptLine *t101 = new TranscriptLine("supercontig12.3", "gene6", "t", "", "", "", 'r', 72, 80, '+');


    cerr << "Positional sort testing  testing: " << endl;
    TranscriptLine *d2 = new TranscriptLine("supercontig12.1", "gene1", "t", "", "", "", 'r', 22, 35, '+');
    //Positional sorting testing 
    AVLTree tree2('s');
    tree2.Insert(t11);
    tree2.Insert(t21);
    tree2.Insert(t31);
    tree2.Insert(t41);
    tree2.Insert(t51);
    tree2.Insert(t61);
    tree2.Insert(t71);
    tree2.Insert(t81);
    tree2.Insert(t91);
    tree2.Insert(t101);
    tree2.InorderTraverse();
    tree2.Delete(d2);
    cerr << "\n" << endl;
    tree2.InorderTraverse();




}
