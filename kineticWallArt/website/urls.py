from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('index', views.index, name='index'),
    path('animator', views.animator, name='animator'),

    path('clear', views.clear, name='clear'),
    path('sync', views.sync, name='sync'),
    path('setpattern', views.setpattern, name='setpattern'),
    path('previewpattern', views.previewpattern, name='previewpattern'),
    # path('deletepattern', views.deletepattern, name='deletepattern'),
    path('deletepattern/<int:pattern_id>', views.deletepattern, name='deletepattern'),
    path('savepattern', views.savepattern, name='savepattern'),
]
