# Generated by Django 3.0 on 2021-02-03 13:57

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('website', '0001_initial'),
    ]

    operations = [
        migrations.RenameModel(
            old_name='Image',
            new_name='Pattern',
        ),
        migrations.RenameField(
            model_name='cross',
            old_name='image',
            new_name='pattern',
        ),
    ]
