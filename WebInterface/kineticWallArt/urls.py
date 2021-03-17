from django.contrib import admin
from django.shortcuts import redirect
from django.urls import include, path
from django.views.generic import RedirectView

urlpatterns = [
    path('website/', include('website.urls')),
    path('', RedirectView.as_view(url='/website/index')),
    path('admin/', admin.site.urls),
]
