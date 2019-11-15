using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AdCap_
{
    public partial class Form1 : Form
    {
        string pointerMoney;
        string pointerXn;
        Memory_managment mem;

        public Form1()
        {
            InitializeComponent();

            pointerXn = "mono-2.0-bdwgc.dll+0039CC44,420,418,450,F48,98,8,18";
            pointerMoney = "mono-2.0-bdwgc.dll+0039B56C,6CC,10,64,28,18";
            mem = new Memory_managment();
        }

        private void textBoxXnAmmount_MouseHover(object sender, EventArgs e)
        {
            if (textBoxXnAmmount.Text == "Buy xN")
            {
                textBoxXnAmmount.Text = "";

                labelMoreInfoXn.Text = "If you put 15, every upgrade you buy will buy 15 upgrades\nlike the in-game option but this gives you more control";
                labelMoreInfoXn.ForeColor = Color.Green;
            }

            else
            {
                labelMoreInfoXn.Text = "";
            }
        }


        private void textBoxSetMoney_MouseHover(object sender, EventArgs e)
        {
            if (textBoxSetMoney.Text == "Set money")
            {
                textBoxSetMoney.Text = "";

            }

           
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            

        }

        private void buttonApplyXn_Click(object sender, EventArgs e)
        {
            string value = textBoxXnAmmount.Text;
            mem.setStatus(pointerXn, "int", value);
        }

        private void buttonApplySetMoney_Click(object sender, EventArgs e)
        {
            string value = textBoxSetMoney.Text;

            mem.setStatus(pointerMoney, "double", value);
        }
    }
}
